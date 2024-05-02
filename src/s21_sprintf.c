#include <stdio.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  size_t curr = 0;
  for (char *ptr = (char *)format; *ptr; ptr++) {
    if (*ptr != '%') {
      str[curr] = *ptr;
    } else {
      ptr++;
      options opts;
      while (get_flag(&opts, ptr)) {
        ptr++;
      }
      ptr = get_width(args, &opts, ptr);
      ptr = get_precision(args, &opts, ptr);
      ptr = get_length(&opts, ptr);
      opts.specifier = *ptr;
/*       printf("Flags: %d %d %d %d %d\n", opts.left_justify, opts.with_sign,
             opts.space, opts.hash, opts.set_zeroes);
      printf("Width and precision: %d %d\n", opts.width, opts.precision);
      printf("Length and specifier: %c %c\n", opts.length, opts.specifier); */
      break;
    }
    curr++;
  }

  va_end(args);
  str++;
  return 1;
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
    opts->width = parse_num_from_ascii(&ptr);
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
      opts->precision = parse_num_from_ascii(&ptr);
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

int parse_num_from_ascii(char **str) {
  int num = ((int)**str - ZERO_NUMBER_IN_ASCII);
  (*str)++;
  while (ZERO_NUMBER_IN_ASCII <= **str && **str <= NINE_NUMBER_IN_ASCII) {
    num *= 10;
    num += ((int)**str - ZERO_NUMBER_IN_ASCII);
    (*str)++;
  }
  return num;
}
