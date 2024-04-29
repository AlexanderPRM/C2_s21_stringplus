#include "s21_string.h"

size_t s21_strlen(const char *str){
    size_t len = 0;
    for(char *ptr = (char *)str; *ptr; ptr++) len++;
    return len;
}