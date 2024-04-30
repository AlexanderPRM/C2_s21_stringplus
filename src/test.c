#include <stdio.h>
#include <string.h>
#include "s21_string.h"


int main() {
  /* Ваши тесты (НЕ ПУШИТЬ НА ГИТХАБ, ОНЛИ ЛОКАЛЬНЫЕ ПРОВЕРКИ)*/

  char dest[10] = "";
  char src[5] = "23";
  strncpy(dest, src, 100);

  size_t length = 0;
  while (src[length]) {
    length++;
  }

  size_t size = n > length ? length + 1: n;
  for (size_t cnt = 0; cnt < size; cnt++) {
    dest[cnt] = src[cnt];
  }

  return 0;
}
