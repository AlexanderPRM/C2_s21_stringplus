#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = NULL;
  size_t src_length = s21_strlen(src);
  size_t str_length = s21_strlen(str);
  res = calloc(src_length + str_length + 1, sizeof(char));
  if (res && start_index <= src_length) {
    if (!str) {
      s21_strncpy(res, src, src_length);
    } else {
      s21_strncpy(res, src, start_index);
      res = res + start_index;
      s21_strncpy(res, str, str_length);
      res = res + str_length;
      src = src + start_index;
      s21_strncpy(res, src, src_length - start_index);
      res = res - str_length - start_index;
    }
  }
  return res;
}
