#include <stdio.h>

size_t strlen(const char *str);

int main() {
    printf("%d\n", strlen("bob"));
    return 0;
}

size_t strlen(const char *str){
   size_t len = 0;
   for (size_t i = 0; str[i] != '0'; i++) {
        len++;
        str++;
   }
   return len;
}