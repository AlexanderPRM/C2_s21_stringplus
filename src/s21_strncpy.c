#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t size = n > s21_strlen(src) ? s21_strlen(src) + 1 : n;
  for (size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
  return dest;
}