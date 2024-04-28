#include "s21_string.h"
#include <stdbool.h>

bool is_delimiter(const char ch, const char *delim) {
    while (*delim) {
        if (ch == *delim) {
            return true;
        }
        delim++;
    }
    return false;
}

char *s21_strtok(char *str, const char *delim) {
    static char *backup;

    if (!str) {
        str = backup;
    }
    if (!str) {
        return NULL;
    }

    while(is_delimiter(*str, delim)) {
        str++;
    }

    char *ptr = str;
    while (*ptr) { 
        if (is_delimiter(*ptr, delim)) {
            *ptr = '\0';
            backup = ptr + 1;
            break;
        }
        ptr++;
        if (*ptr == '\0') {
            backup = NULL;
        } 
    }
    return str;
}