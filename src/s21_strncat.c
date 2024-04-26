#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  char *ptr = dest;
  while (*ptr) {
    ptr++;
  }

  for (size_t cnt = 0; src[cnt] != '\0' && cnt < n; cnt++) {
    *ptr++ = src[cnt];
  }
  return dest;
}
