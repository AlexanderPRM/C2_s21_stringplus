#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char result[BUFFER_SIZE] = "\0";
  s21_memset(result, '\0', BUFFER_SIZE);
#if defined(__linux__)
  char *errors[] = LINUX_MESSAGES;
  if (1 <= errnum && errnum <= 133) {
    s21_strncpy(result, errors[errnum - 1], s21_strlen(errors[errnum - 1]));
  }
#define UNKNOWN_PREFIX "Unknown error "
#elif defined(__APPLE__)
  char *errors[] = APPLE_MESSAGES;
  if (1 <= errnum && errnum <= 106) {
    s21_strncpy(result, errors[errnum - 1], s21_strlen(errors[errnum - 1]));
  }
#define UNKNOWN_PREFIX "Unknown error: "
#endif

  if (!result[0]) {
    size_t prefix_len = s21_strlen(UNKNOWN_PREFIX);
    char res[BUFFER_SIZE] = "\0";
    s21_memset(res, '\0', sizeof(char) * BUFFER_SIZE);
    s21_strncpy(res, UNKNOWN_PREFIX, prefix_len);
    char buffer[BUFFER_SIZE] = "\0";
    size_t curr = BUFFER_SIZE - 1;
    int num = errnum;
    bool negative = num < 0;
    num = negative ? -num : num;

    if (num == 0) {
      buffer[0] = '0';
    }

    while (num > 0) {
      curr--;
      buffer[curr] = "0123456789"[num % 10];
      num /= 10;
    }
    char number[BUFFER_SIZE] = "\0";
    char *ptr = number;
    if (negative) {
      *ptr++ = '-';
    }
    while (buffer[curr]) {
      *ptr++ = buffer[curr++];
    }
    s21_strncat(res, number, s21_strlen(number));
    s21_strncpy(result, res, s21_strlen(res));
  }
  return (char *)result;
}
