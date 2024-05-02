#include "s21_string.h"

char *s21_strchr(const char *src, int c){
    char* result = NULL;
    for (char *ptr = (char*)src; *ptr; ptr++){
        if(*ptr == (unsigned char)c) {
            result = ptr;
            break;
        }
    }
    return result;
}