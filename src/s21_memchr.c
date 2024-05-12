#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  while (*ptr && *ptr != ch && n-- > 0) {
    if (n > 0) ptr++;
  }
  if (*ptr == ch) {
    return (void *)ptr;
  }
  return NULL;
}
