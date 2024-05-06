#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "s21_string.h"

START_TEST(test_sprintf_string) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%s", "ascii");

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%s", "ascii");
  ck_assert_str_eq(my_dest, c_dest);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%10.3s", "1f");
  res2 = sprintf(ptr2, "%10.3s", "1f");
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%*.*s", 3213, 6, "$!313");
  res2 = sprintf(ptr2, "%*.*s", 3213, 6, "$!313");
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  setlocale(LC_ALL, "");
  res1 = s21_sprintf(ptr1, "%12.4ls", L"тест");
  res2 = sprintf(ptr2, "%12.4ls", L"тест");
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;
}
END_TEST

TCase *sprintf_string() {
  TCase *tc = tcase_create("Sprintf Long String.");
  tcase_add_test(tc, test_sprintf_string);
  return tc;
}

START_TEST(test_sprintf_char) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%c", 'a');

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%c", 'a');
  ck_assert_str_eq(my_dest, c_dest);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-10c", '!');
  res2 = sprintf(ptr2, "%-10c", '!');
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;
}

TCase *sprintf_char() {
  TCase *tc = tcase_create("Sprintf Char String.");
  tcase_add_test(tc, test_sprintf_char);
  return tc;
}



Suite *s21_sprintf_suite() {
  Suite *s = suite_create("String Functions");
  suite_add_tcase(s, sprintf_string());
  suite_add_tcase(s, sprintf_char());
  return s;
}

int main() {
  int number_failed;
  SRunner *sr = srunner_create(s21_sprintf_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
