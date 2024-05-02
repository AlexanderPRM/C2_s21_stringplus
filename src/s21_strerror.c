#include "s21_string.h"

char *s21_strerror(int errnum) {
  char *result = NULL;

#if defined(__linux__)
  char *errors[] = LINUX_MESSAGES;
  if (1 <= errnum && errnum <= 133) {
    result = errors[errnum - 1];
  }
#elif defined(__APPLE__)
  char *errors[] = APPLE_MESSAGES;
  if (1 <= errnum && errnum <= 106) {
    result = errors[errnum - 1];
  }
#endif

  if (!result) {
    result = "Unknown error";
  }
  return result;
}