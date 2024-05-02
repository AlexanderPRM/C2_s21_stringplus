#include "s21_string.h"
#include <stdbool.h>

char *s21_strpbrk(const char *str1, const char *str2){
    bool flag = false;
    char *result = NULL;
    for(char *ptr = (char *)str1; *ptr && !flag; ptr++) {
        for(char *search = (char *)str2; *search && !flag; search++){
            if(*ptr == *search) {
                flag = true;
                result = ptr;
            }
        }
    }
    return result;
}