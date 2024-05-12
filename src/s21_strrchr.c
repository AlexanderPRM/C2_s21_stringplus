#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = NULL;
  for (char *ptr = (char *)str; *ptr; ptr++) {
    if (*ptr == c) {
      result = ptr;
    }
  }
  return result;
}
