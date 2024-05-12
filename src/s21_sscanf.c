#include "s21_sscanf.h"

#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int result = *str ? 0 : -1;

  char *string = (char *)(str + s21_remove_extra(str));
  if (!*string && *(format + s21_remove_extra(format))) result = -1;

  va_list arguments;
  va_start(arguments, format);

  bool should_break = false;
  for (; *format && result != -1; format++) {
    if (*format == '%') {
      string += s21_remove_extra(string);
      specifier spec = {0};
      format++;

      spec = s21_scan_spec(&format);
      s21_set_value(&result, arguments, spec, &string, str, &format,
                    &should_break);
    } else {
      if (*string == *format) {
        (string)++;
      } else if (*format != ' ' && *format != '\t') {
        should_break = true;
      }
    }

    if (should_break) break;
  }

  va_end(arguments);

  return result;
}

int s21_remove_extra(const char *str) {
  char *ptr = (char *)str;
  int count = 0;

  while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\r' ||
         *ptr == '\x0B' || *ptr == '\f') {
    count++;
    ptr++;
  }

  return count;
}

specifier s21_scan_spec(const char **symbol) {
  specifier spec = {0};

  if (**symbol == '*') {
    spec.skip = true;
    (*symbol)++;
  }

  while (s21_is_digit(**symbol, 10)) {
    spec.width = spec.width * 10 + (**symbol) - '0';
    (*symbol)++;
  }

  if (**symbol == 'h') {
    spec.length |= LENGTH_h;
    (*symbol)++;
  } else if (**symbol == 'L' || (**symbol == 'l' && *(*symbol + 1) == 'l')) {
    spec.length |= LENGTH_L;
    if (**symbol == 'l' && *(*symbol + 1) == 'l')
      *symbol += 2;
    else
      (*symbol)++;
  } else if (**symbol == 'l') {
    spec.length |= LENGTH_l;
    (*symbol)++;
  } else {
    spec.length |= LENGTH_none;
  }

  const char *specs = "cdieEfgGosuxXpn%";
  char *pos = s21_strchr(specs, **symbol);
  spec.specifier = pos ? *pos : spec_unknown;

  return spec;
}

void s21_set_value(int *result, va_list arguments, specifier spec,
                   char **string, const char *str, const char **format,
                   bool *should_break) {
  if (**string) {
    switch (spec.specifier) {
      case 's':
      case 'c':
        *result += s21_spec_c_s(spec, arguments, string);
        break;
      case 'd':
        *result +=
            s21_spec_x_o_d(spec, arguments, string, 10, false, should_break);
        break;
      case 'i':
        *result += s21_spec_i(spec, arguments, string, should_break);
        break;
      case 'e':
      case 'E':
      case 'g':
      case 'G':
      case 'f':
        *result += s21_spec_f_e_g(spec, arguments, string);
        break;
      case 'o':
        *result +=
            s21_spec_x_o_d(spec, arguments, string, 8, false, should_break);
        break;
      case 'u':
        *result += s21_spec_u(spec, arguments, string, should_break);
        break;
      case 'p':
        spec.length = LENGTH_l;
        *result +=
            s21_spec_x_o_d(spec, arguments, string, 16, false, should_break);
        break;
      case 'x':
      case 'X':
        *result +=
            s21_spec_x_o_d(spec, arguments, string, 16, false, should_break);
        break;
      case 'n':
        *va_arg(arguments, long int *) = *string - str;
        break;
      case '%':
        s21_spec_percent(string, format, result, should_break);
        break;
      case '?':
        *result = -1;
        break;
    }
  }

  *string += s21_remove_extra(*string);
}

bool s21_is_digit(const char symbol, int base) {
  bool result = false;

  if (base <= 10) {
    result = symbol >= '0' && symbol < '0' + base;
  } else {
    result = (symbol >= '0' && symbol <= '9') ||
             (symbol >= 'A' && symbol < 'A' + base - 10) ||
             (symbol >= 'a' && symbol < 'a' + base - 10);
  }

  return result;
}

size_t s21_to_digit(const char symbol, int base) {
  size_t result = 0;
  if (base <= 10) {
    result = symbol - '0';
  } else {
    if (symbol <= '9') {
      result = symbol - '0';
    } else if (symbol <= 'A' + base - 10) {
      result = symbol - 'A' + 10;
    } else {
      result = symbol - 'a' + 10;
    }
  }
  return result;
}

bool s21_is_hex_prefix(char **string, int width) {
  return **string == '0' && (*(*string + 1) == 'x' || *(*string + 1) == 'X') &&
         *(*string + 2) != ' ' && *(*string + 2) != '\0' && width - 2 != 0;
}

int s21_spec_x_o_d(specifier spec, va_list arguments, char **string,
                   int number_system, bool negative, bool *should_break) {
  int result = 0;
  bool is_negative = negative;
  bool width_was_added = spec.width > 0;

  if (**string == '-' && spec.width != 1 && !negative) {
    (*string)++;
    spec.width--;
    is_negative = true;
    if (**string == '-' || **string == '+') *should_break = true;
  } else if (**string == '+' && spec.width != 1) {
    (*string)++;
    spec.width--;
    if (**string == '-' || **string == '+') *should_break = true;
  }

  if (s21_is_hex_prefix(string, spec.width) && spec.specifier != 'o') {
    *string += 2;
    spec.width -= 2;
    if (spec.specifier == 'p') result |= 1;
  }

  if (!spec.skip && !(width_was_added && spec.width <= 0)) {
    result |= s21_parse_based_uint(spec, string, arguments, is_negative,
                                   number_system);
  } else if (spec.skip) {
    while (**string != ' ') (*string)++;
  }

  return result;
}

int s21_spec_u(specifier spec, va_list arguments, char **string,
               bool *should_break) {
  int result = 0;
  bool is_negative = false;
  bool error = false;

  if ((**string == '-' || **string == '+') && spec.width == 1) {
    *should_break = true;
    error = true;
  } else if (**string == '-' && *(*string + 1) != '-') {
    (*string)++;
    spec.width--;
    is_negative = true;
  } else if (**string == '+') {
    (*string)++;
    spec.width--;
  } else if (*(*string + 1) == '-') {
    error = true;
  }

  if (!error && !spec.skip) {
    result = s21_parse_based_uint(spec, string, arguments, is_negative, 10);
  }

  return result;
}

int s21_parse_based_uint(specifier spec, char **string, va_list arguments,
                         bool is_negative, int base) {
  unsigned long long result = 0;
  if (s21_scan_based_uint(&result, string, spec.width, is_negative, base,
                          spec)) {
    if (spec.length & LENGTH_h)
      *(va_arg(arguments, unsigned short *)) = (unsigned short)result;
    if (spec.length & LENGTH_l)
      *(va_arg(arguments, unsigned long *)) = (unsigned long)result;
    if (spec.length & LENGTH_L)
      *(va_arg(arguments, unsigned long long *)) = (unsigned long long)result;
    if (spec.length & LENGTH_none)
      *(va_arg(arguments, unsigned int *)) = (unsigned int)result;
    result = 1;
  }

  return result;
}

bool s21_scan_based_uint(unsigned long long *result, char **string, int width,
                         bool is_negative, int base, specifier spec) {
  bool number_was_found = false;
  unsigned long long res = 0;
  int flag = 0;

  if (width <= 0) width = INT_MAX;

  if (s21_is_digit(**string, base)) {
    number_was_found = true;
    while (s21_is_digit(**string, base) && width-- && flag == 0) {
      res = res * base + (int)s21_to_digit(**string, base);
      (*string)++;
      if (res > LONG_MAX &&
          ((spec.length & LENGTH_h) || (spec.length & LENGTH_none))) {
        res = -1;
        flag = 1;
      } else if (res > LONG_MAX && (spec.length & LENGTH_l)) {
        res = LONG_MAX;
        flag = 1;
      }
    }
  }

  if (!is_negative) {
    *result = res > LONG_MAX ? LONG_MAX : res;
  } else if (res == 0) {
    *result = res;
    number_was_found = true;
  } else if (res == LONG_MAX) {
    *result = -res - 1;
  } else {
    *result = res > LONG_MAX ? 0 : -res;
  }

  return number_was_found;
}

void s21_spec_percent(char **string, const char **format, int *result,
                      bool *should_break) {
  if (**string == **format) {
    (*string)++;
  } else {
    *result = 0;
    *should_break = true;
  }
}

int s21_spec_i(specifier spec, va_list arguments, char **string,
               bool *should_break) {
  int result = 0;

  if (!spec.width) spec.width = INT_MAX;

  bool is_negative = false;
  if (**string == '-' && (*(*string + 1) == '0') && spec.width != 1) {
    (*string)++;
    spec.width--;
    is_negative = true;
  } else if (**string == '+' && (*(*string + 1) == '0') && spec.width != 1) {
    (*string)++;
    spec.width--;
  }

  if (**string == '0' && spec.width > 2) {
    (*string)++;
    if (**string == 'x' || **string == 'X') {
      (*string)++;
      spec.width -= 2;
      result = s21_spec_x_o_d(spec, arguments, string, 16, is_negative,
                              should_break);
    } else {
      result =
          s21_spec_x_o_d(spec, arguments, string, 8, is_negative, should_break);
    }
  } else {
    result = s21_spec_u(spec, arguments, string, should_break);
  }

  return result;
}

int s21_spec_c_s(specifier spec, va_list arguments, char **string) {
  int result = 0;
  char *pointer = (char *)va_arg(arguments, int *);

  if (spec.width == 0) {
    spec.width = spec.specifier == 'c' ? 1 : INT_MAX;
  }

  while (**string && spec.width > 0 && (**string != ' ' && **string != '\t') &&
         !spec.skip) {
    result = 1;
    *pointer++ = **string;
    (*string)++;
    spec.width--;
  }

  if (spec.specifier == 's' && !spec.skip) {
    *pointer = '\0';
  }

  return result;
}

int s21_spec_f_e_g(specifier spec, va_list arguments, char **string) {
  int result = 0;
  if (spec.width == 0) spec.width = INT_MAX;

  long double f_number = 0;
  result = s21_scan_float(&f_number, string, spec.width) && !spec.skip;

  if (result) {
    if (spec.length & LENGTH_l) {
      *(va_arg(arguments, double *)) = (double)f_number;
    } else if (spec.length & LENGTH_L) {
      *(va_arg(arguments, long double *)) = (double)f_number;
    } else if (spec.length & LENGTH_none) {
      *(va_arg(arguments, float *)) = (float)f_number;
    }
  }

  return result;
}

int s21_scan_float(long double *number, char **string, int width) {
  long double result = 0;
  bool is_negative = false;
  bool was_found = 0;

  if (**string == '-') {
    is_negative = true;
    width--;
    (*string)++;
  } else if (**string == '+') {
    width--;
    (*string)++;
  }

  if (s21_is_nan_or_inf(string, &result)) {
    was_found = true;
  } else if (s21_is_digit(**string, 10) || **string == '.') {
    was_found = **string != '.' ? true : s21_is_digit(*(*string + 1), 10);
    result = s21_atof(string, &width);
    s21_scientific(&result, string, &width);
  } else if (is_negative) {
    (*string)--;
  }

  if (was_found) {
    *number = is_negative ? -result : result;
  }

  return was_found;
}

bool s21_is_nan_or_inf(char **string, long double *result) {
  if (s21_strstr_sscanf(string, "nan")) {
    *result = NAN;
  } else if (s21_strstr_sscanf(string, "inf")) {
    *result = INFINITY;
  }

  return isnan(*result) || isinf(*result);
}

bool s21_strstr_sscanf(char **str, char *pat) {
  bool res = false;
  char *s = *str;
  while (*s && s21_to_lower_sscanf(*s) == s21_to_lower_sscanf(*pat)) {
    s++;
    pat++;
  }
  if (*pat == '\0') {
    *str = s;
    res = true;
  }
  return res;
}

char s21_to_lower_sscanf(char c) {
  if (c >= 'A' && c <= 'Z') {
    c += 'a' - 'A';
  }
  return c;
}

long double s21_atof(char **string, int *width) {
  long double result = 0;

  while (s21_is_digit(**string, 10) && *width) {
    result = result * 10 + (**string - '0');
    (*string)++;
    (*width)--;
  }

  if (**string == '.') {
    (*string)++;
    (*width)--;
    long double frac_part = 1;

    while (s21_is_digit(*(*string), 10) && (*width)--) {
      frac_part /= 10;
      result += frac_part * (**string - '0');
      (*string)++;
    }
  }

  return result;
}

void s21_scientific(long double *result, char **string, int *width) {
  long long exp = 0;
  if (**string == 'e' || **string == 'E') {
    (*string)++;
    (*width)--;
    s21_scan_int(string, width, &exp);
  }

  *result *= pow(10, exp);
}

void s21_scan_int(char **string, int *width, long long *result) {
  bool is_negative = false;
  bool flag = false;
  unsigned long long res = 0;

  if (*width <= 0) *width = INT_MAX;

  if (**string == '-') {
    is_negative = true;
    (*string)++;
    (*width)--;
  } else if (**string == '+') {
    (*string)++;
    (*width)--;
  }

  if (s21_is_digit(**string, 10)) {
    while (s21_is_digit(**string, 10) && width-- && !flag) {
      if (res > (unsigned long long)(LLONG_MAX - (**string - '0')) / 10) {
        flag = true;
        res = LLONG_MAX;
        if (is_negative) res = -res - 1;
        while (**string && width--) (*string)++;
        break;
      }
      res = res * 10 + (**string - '0');
      (*string)++;
    }
  } else {
    (*string)--;
  }

  *result = is_negative ? -res : res;
}
