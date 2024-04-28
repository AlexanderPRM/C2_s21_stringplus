#include "s21_string.h"

size_t s21_strcspn(const char *str1, const char *str2) {
  size_t len = 0;
  for (char *ptr1 = (char *)str1; *ptr1; ptr1++) {
    char *ptr2 = (char *)str2;
    while (*ptr2 && *ptr1 != *ptr2) {
      ptr2++;
    }
    if (*ptr1 == *ptr2) {
      break;
    }
    len++;
  }
  return len;
}
