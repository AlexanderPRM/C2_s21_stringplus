#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t curr = 0;
  for (; dest[curr]; curr++) {
  }
  for (size_t cnt = 0; src[cnt] != '\0' && cnt < n; cnt++) {
    dest[curr] = src[cnt];
    curr++;
  }
  return dest;
}
