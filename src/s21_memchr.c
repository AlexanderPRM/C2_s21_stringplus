#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  while (*ptr && *ptr != ch && n--) {
    ptr++;
  }
  if (*ptr == ch) {
    return ptr;
  }
  return NULL;
}