#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  const char trim_default[] = " \t\n";
  size_t cut_left, cut_right, size_src, size_trim, size_fin;

  cut_left = cut_right = size_trim = 0;
  size_src = (src == NULL) ? 0 : s21_strlen(src);

  if (trim_chars == NULL || s21_strlen(trim_chars) == 0) {
    trim_chars = trim_default;
  }

  size_trim = s21_strlen(trim_chars);

  size_t i;
  for (i = size_src; i > 0 && s21_strchr(trim_chars, src[i - 1]); i--) {
    cut_right++;
  }
  size_fin = size_src - cut_right;

  for (i = 0; i < size_fin && s21_strchr(trim_chars, src[i]); i++) {
    cut_left++;
  }
  size_fin -= cut_left;

  char *fin = (char *)calloc(size_fin + 1, sizeof(char));
  if (fin != NULL) {
    for (i = cut_left; i < size_src - cut_right; i++) {
      fin[i - cut_left] = src[i];
    }
  }
  return fin;
}
