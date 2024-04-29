#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    char* result = NULL;
    for (char *ptr = (char *)haystack; *ptr; ptr++){
        if (*ptr == *needle) {
            char *curr = (char *)needle;
            char *curr_second = ptr;
            while (*curr == *curr_second) {
                curr++;
                curr_second++;
            }
            if(*curr == '\0') {
                result = ptr;
                break;
            }
        }
    }
    return result;
}