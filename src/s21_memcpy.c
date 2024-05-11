#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;
  int result = 0;
  for (size_t i = 0; i < n; i++) {
    ptr1[i] = ptr2[i];
  }
  return dest;
}
