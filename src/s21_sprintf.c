#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "");
  va_list args;
  va_start(args, format);
  size_t curr = 0;
  while (*format) {
    char *ptr = (char *)format;
    if (*ptr != '%') {
      str[curr++] = *ptr++;
    } else {
      ptr++;
      options opts = {false, false, false, false, false,
                      0,     0,     false, '\0',  '\0'};
      while (get_flag(&opts, ptr)) {
        ptr++;
      }
      ptr = get_width(args, &opts, ptr);
      ptr = get_precision(args, &opts, ptr);
      ptr = get_length(&opts, ptr);
      opts.specifier = *ptr++;
      handle_specifier(args, opts, str, &curr);
    }
    format = ptr;
  }
  str[curr] = '\0';
  va_end(args);
  return 1;
}

void handle_specifier(va_list args, options opts, char *dest, size_t *curr) {
  char buffer[BUFFER_SIZE] = "\0";

  if (opts.specifier == 'd' || opts.specifier == 'i') {
    parse_int(args, opts, buffer);
  } else if (opts.specifier == 'c') {
    parse_char(args, opts, buffer);
  } else if (opts.specifier == '%') {
    buffer[0] = '%';
  }

  for (size_t i = 0; buffer[i]; i++, (*curr)++) {
    dest[*curr] = buffer[i];
  }
}

void parse_char(va_list args, options opts, char *dest) {
  size_t curr = 0;
  size_t char_length = opts.length == 'l' ? 2 : 1;
  if (!opts.left_justify && opts.width > char_length) {
    for (size_t i = opts.width - char_length; i > 0; i--) {
      dest[curr++] = ' ';
    }
  }
  if (opts.length == 'l') {
    char buff[MB_CUR_MAX];
    s21_memset(buff, '\0', MB_CUR_MAX);
    wchar_t ch = va_arg(args, wchar_t);
    wcrtomb(buff, ch, NULL);
    for (size_t i = 0; buff[i]; i++) dest[curr++] = buff[i];
  } else {
    char ch = va_arg(args, int);
    dest[curr++] = ch;
  }

  if (opts.left_justify && opts.width > char_length) {
    for (size_t i = opts.width - char_length; i > 0; i--) {
      dest[curr++] = ' ';
    }
  }
}

void parse_int(va_list args, options opts, char *dest) {
  long num;
  switch (opts.length) {
    case 'l':
      num = va_arg(args, long);
      break;
    case 'h':
      num = (long)va_arg(args, long);
      num = (short int)num;
      break;
    default:
      num = (long)va_arg(args, int);
      break;
  }

  char number[BUFFER_SIZE] = "\0";
  parse_int_to_ascii(num, 10, number);
  size_t chars_length = 0;
  if ((num >= 0 && (opts.space || opts.with_sign)) || num < 0) {
    chars_length = 1;
  }
  size_t num_length = s21_strlen(number);
  if (num < 0) {
    num_length--;
  }
  size_t zeroes_for_add = 0;
  chars_length += num_length;
  if (opts.precision_set && opts.precision > num_length) {
    zeroes_for_add = opts.precision - num_length;
  } else if (opts.set_zeroes && opts.width > chars_length) {
    zeroes_for_add = opts.width - chars_length;
  }
  chars_length += zeroes_for_add;
  add_int_to_string(dest, opts, chars_length, num_length, zeroes_for_add, num,
                    number);
}

void add_int_to_string(char *dest, options opts, size_t chars_length,
                       size_t num_length, size_t zeroes_for_add, long num,
                       char *num_str) {
  size_t curr = 0;
  if (num >= 0 && opts.space && !opts.with_sign) {
    dest[curr++] = ' ';
  }

  if (!opts.left_justify && !opts.set_zeroes) {
    if (chars_length < opts.width) {
      for (size_t i = opts.width - chars_length; i > 0; i--) {
        dest[curr++] = ' ';
      }
    }
  }

  if (num >= 0 && opts.with_sign) {
    dest[curr++] = '+';
  } else if (num < 0) {
    dest[curr++] = '-';
    num_str++;
  }

  for (size_t i = 0; i < zeroes_for_add; i++) {
    dest[curr++] = '0';
  }
  for (size_t i = 0; i < num_length; i++) {
    dest[curr++] = num_str[i];
  }

  if (opts.left_justify && !opts.set_zeroes) {
    if (chars_length < opts.width) {
      for (size_t i = opts.width - chars_length; i > 0; i--) {
        dest[curr++] = ' ';
      }
    }
  }
}

bool get_flag(options *opts, char *ptr) {
  bool is_flag = true;
  switch (*ptr) {
    case '-':
      opts->left_justify = true;
      break;
    case '+':
      opts->with_sign = true;
      break;
    case ' ':
      opts->space = true;
      break;
    case '#':
      opts->hash = true;
      break;
    case '0':
      opts->set_zeroes = true;
      break;
    default:
      is_flag = false;
      break;
  }
  return is_flag;
}

char *get_width(va_list args, options *opts, char *ptr) {
  if (*ptr == '*') {
    opts->width = va_arg(args, int);
    ptr++;
  } else if (ZERO_NUMBER_IN_ASCII < *ptr && *ptr <= NINE_NUMBER_IN_ASCII) {
    opts->width = parse_int_from_ascii(&ptr);
  }
  return ptr;
}

char *get_precision(va_list args, options *opts, char *ptr) {
  if (*ptr == '.') {
    opts->precision_set = true;
    ptr++;
    if (*ptr == '*') {
      opts->precision = va_arg(args, int);
      ptr++;
    } else if (ZERO_NUMBER_IN_ASCII <= *ptr && *ptr <= NINE_NUMBER_IN_ASCII) {
      opts->precision = parse_int_from_ascii(&ptr);
    }
  }
  return ptr;
}

char *get_length(options *opts, char *ptr) {
  if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L') {
    opts->length = *ptr;
    ptr++;
  }
  return ptr;
}

int parse_int_from_ascii(char **str) {
  int num = ((int)**str - ZERO_NUMBER_IN_ASCII);
  (*str)++;
  while (ZERO_NUMBER_IN_ASCII <= **str && **str <= NINE_NUMBER_IN_ASCII) {
    num *= 10;
    num += ((int)**str - ZERO_NUMBER_IN_ASCII);
    (*str)++;
  }
  return num;
}

void parse_int_to_ascii(long num, int base, char *dest) {
  char buffer[BUFFER_SIZE] = "\0";
  size_t curr = BUFFER_SIZE - 1;
  char *digits = "0123456789abcdef";
  bool negative = num < 0;
  num = negative ? -num : num;

  if (num == 0) {
    dest[0] = '0';
  }

  while (num > 0) {
    curr--;
    buffer[curr] = digits[num % base];
    num /= base;
  }

  size_t idx = 0;
  if (negative) {
    dest[idx++] = '-';
  }
  while (buffer[curr]) {
    dest[idx++] = buffer[curr++];
  }
}
