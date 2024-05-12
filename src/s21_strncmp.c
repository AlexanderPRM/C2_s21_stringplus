#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int answer = 0;
  for (size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      answer = str1[i] - str2[i];
    }
  }
  return answer;
}
