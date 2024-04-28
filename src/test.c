#include <stdio.h>
#include <string.h>


#include "s21_string.h"

int main() {
  /*   char dest[4] = "123";
    char src[15] = "12491294192";
    strncat(dest, src, 3);

    char dest2[10] = "123";
    char src2[15] = "12";
    s21_strncat(dest2, src2, 6);

    printf("%s\n", dest);
    printf("%s\n", dest2); */

  /* char *src = "12faksfaj102413";
  char sym[20] = "j";
  printf("%lu", s21_strcspn(src, sym)); */

  /*   char src[20] = "12faksfaj102413";
    char *ptr = s21_memchr(src, 'a', -1);
    if (ptr == NULL) {
      printf("NULL");
    } else {
      *ptr = '3';
      printf("%s", src);
    } */

/*   char src[40] = "////////";
  char *res = s21_strtok(src, "/");
  printf("%s\n", res);
  do {
    printf("%s\n", res);
    res = s21_strtok(NULL, "/");
    if (res == NULL) {
      break;
    }
  } while (*res);
 */

  printf("%s\n", strerror(1294129491));
  return 0;
}
