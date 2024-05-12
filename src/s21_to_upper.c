#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = NULL;
  res = calloc(s21_strlen(str) + 1, sizeof(char));
  size_t curr = 0;
  if (res) {
    for (char *ptr = (char *)str; *ptr; ptr++, curr++) {
      if (*ptr >= 'a' && *ptr <= 'z') {
        res[curr] = *ptr - 32;
      } else {
        res[curr] = *ptr;
      }
    }

    res[curr] = '\0';
    res = res;
  }
  return res;
}
