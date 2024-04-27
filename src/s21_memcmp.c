#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
    unsigned char *ptr1 = (unsigned char *)str1;
    unsigned char *ptr2 = (unsigned char *)str2;
    int result = 0;

    for(size_t s = 0; s < n; s++){
        if(ptr1[s] != ptr2[s]){
            result = 1;
        }
    }
    return result;
}