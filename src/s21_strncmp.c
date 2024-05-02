#include "s21_string.h"

int strncmp(const char *str1, const char *str2, size_t n) {
  int bob = 0;
  for (size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      bob = str1[i] - str2[i];
    }
  }

  return bob;
}
