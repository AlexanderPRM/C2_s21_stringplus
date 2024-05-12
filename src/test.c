#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sscanf.h"
#include "s21_string.h"

// Sprintf functions

START_TEST(test_sprintf_string) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%s 123", "ascii");

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%s 123", "ascii");
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
  TCase *tc = tcase_create("Sprintf String test.");
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
  TCase *tc = tcase_create("Sprintf Char test.");
  tcase_add_test(tc, test_sprintf_char);
  return tc;
}

START_TEST(test_sprintf_int) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%d", 1242491);

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%d", 1242491);
  ck_assert_str_eq(my_dest, c_dest);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-10d", 101);
  res2 = sprintf(ptr2, "%-10d", 101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-+10.5d", 101);
  res2 = sprintf(ptr2, "%-+10.5d", 101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%- 100.10d", 101);
  res2 = sprintf(ptr2, "%- 100.10d", 101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "% 100.10d", -101);
  res2 = sprintf(ptr2, "% 100.10d", -101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "% 100.10hd", (short int)-101202104041201);
  res2 = sprintf(ptr2, "% 100.10hd", (short int)-101202104041201);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "% 100.10ld", (long)-101202104041201);
  res2 = sprintf(ptr2, "% 100.10ld", (long)-101202104041201);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;
}

TCase *sprintf_int() {
  TCase *tc = tcase_create("Sprintf Int test.");
  tcase_add_test(tc, test_sprintf_int);
  return tc;
}

START_TEST(test_sprintf_float) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%f", (double)1242491);

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%f", (double)1242491);
  ck_assert_str_eq(my_dest, c_dest);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-10f", 101.4124);
  res2 = sprintf(ptr2, "%-10f", 101.4124);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-+10.5f", 101.00000001);
  res2 = sprintf(ptr2, "%-+10.5f", 101.00000001);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%- 100.10f", (double)101);
  res2 = sprintf(ptr2, "%- 100.10f", (double)101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "% 100.10f %%", (double)-101);
  res2 = sprintf(ptr2, "% 100.10f %%", (double)-101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;
}

TCase *sprintf_float() {
  TCase *tc = tcase_create("Sprintf Float test.");
  tcase_add_test(tc, test_sprintf_float);
  return tc;
}

START_TEST(test_sprintf_uint) {
  char my_dest[BUFFER_SIZE] = "\0";
  char *ptr1 = my_dest;
  size_t res1 = 0;
  res1 = s21_sprintf(ptr1, "%u", 1242491);

  char c_dest[BUFFER_SIZE] = "\0";
  char *ptr2 = c_dest;
  size_t res2 = 0;
  res2 = sprintf(ptr2, "%u", 1242491);
  ck_assert_str_eq(my_dest, c_dest);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-10u", 101);
  res2 = sprintf(ptr2, "%-10u", 101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%020u", 10421491);
  res2 = sprintf(ptr2, "%020u", 10421491);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%-100.10u", 101);
  res2 = sprintf(ptr2, "%-100.10u", 101);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%100.10hu %%", (short int)42999219419);
  res2 = sprintf(ptr2, "%100.10hu %%", (short int)42999219419);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;

  res1 = s21_sprintf(ptr1, "%100.10lu %%", 42999219419);
  res2 = sprintf(ptr2, "%100.10lu %%", 42999219419);
  ck_assert_str_eq(ptr1, ptr2);
  ptr1 += res1;
  ptr2 += res2;
}

TCase *sprintf_uint() {
  TCase *tc = tcase_create("Sprintf Unsigned Int test.");
  tcase_add_test(tc, test_sprintf_uint);
  return tc;
}

Suite *s21_sprintf_suite() {
  Suite *s = suite_create("Sprintf Functions");
  suite_add_tcase(s, sprintf_string());
  suite_add_tcase(s, sprintf_char());
  suite_add_tcase(s, sprintf_int());
  suite_add_tcase(s, sprintf_float());
  suite_add_tcase(s, sprintf_uint());
  return s;
}

// Scanf tests

START_TEST(test_sscanf) {
  char res[BUFFER_SIZE] = "\0";
  int first, second, third;
  unsigned int uint;
  s21_sscanf("test 1 2 100000 -1000", "%s %hd %li %u %d", res, &first, &second,
             &uint, &third);
  ck_assert_str_eq(res, "test");
  ck_assert_int_eq(first, 1);
  ck_assert_int_eq(second, 2);
  ck_assert_int_eq(uint, 100000);
  ck_assert_int_eq(third, -1000);

  float floating;
  s21_sscanf("test1234jfsajf12l3 1.23", "%s %f", res, &floating);
  ck_assert_str_eq(res, "test1234jfsajf12l3");
  ck_assert_double_eq(floating, (float)1.23);

  int hex;
  s21_sscanf("0x12345678", "%x", &hex);
  ck_assert_int_eq(hex, 0x12345678);

  int pointer_address;
  s21_sscanf("0x1ff23", "%p", &pointer_address);
  ck_assert_int_eq(pointer_address, 0x1ff23);
}

TCase *sscanf_string() {
  TCase *tc = tcase_create("Sscanf string test.");
  tcase_add_test(tc, test_sscanf);
  return tc;
}

Suite *s21_sscanf_suite() {
  Suite *s = suite_create("Sscanf Functions");
  suite_add_tcase(s, sscanf_string());
  return s;
}

// Memory functions

START_TEST(test_memchr) {
  char my_dest[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char *res1 = s21_memchr(my_dest, (int)'1', 6);
  char *res2 = memchr(my_dest, (int)'1', 6);
  ck_assert_ptr_eq(res1, res2);

  res1 = s21_memchr(my_dest, (int)'1', 100);
  res2 = memchr(my_dest, (int)'1', 100);
  ck_assert_str_eq(res1, res2);

  res1 = s21_memchr(my_dest, (int)'0', 100);
  res2 = memchr(my_dest, (int)'0', 100);
  ck_assert_str_eq(res1, res2);

  res1 = s21_memchr(my_dest, (int)'(', 100);
  res2 = memchr(my_dest, (int)'(', 100);
  ck_assert_str_eq(res1, res2);

  res1 = s21_memchr(my_dest, (int)'.', 100);
  res2 = memchr(my_dest, (int)'.', 100);
  ck_assert_ptr_eq(res1, res2);
}

TCase *memchr_test() {
  TCase *tc = tcase_create("Memchr test.");
  tcase_add_test(tc, test_memchr);
  return tc;
}

START_TEST(test_memcmp) {
  char str1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char str2[BUFFER_SIZE] = "49492912941jfsa";
  int res1 = s21_memcmp(str1, str2, 10);
  int res2 = memcmp(str1, str2, 10);
  ck_assert_int_eq(res1, res2);

  char str3[BUFFER_SIZE] = "49492912939(@(!())00fsja)";
  char str4[BUFFER_SIZE] = "49492912141jfsa";
  res1 = s21_memcmp(str3, str4, 10);
  res2 = memcmp(str3, str4, 10);
  ck_assert_int_eq(res1, res2);
}

TCase *memcmp_test() {
  TCase *tc = tcase_create("Memcmp test.");
  tcase_add_test(tc, test_memcmp);
  return tc;
}

START_TEST(test_memcpy) {
  char dest[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src[BUFFER_SIZE] = "49492912941jfsa";

  char dest2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src2[BUFFER_SIZE] = "49492912941jfsa";

  void *res1 = s21_memcpy(dest, src, 10);
  void *res2 = memcpy(dest2, src2, 10);

  ck_assert_str_eq(res1, res2);

  res1 = s21_memcpy(dest, src, 1);
  res2 = memcpy(dest2, src2, 1);

  ck_assert_str_eq(res1, res2);

  res1 = s21_memcpy(dest, src, 1000);
  res2 = memcpy(dest2, src2, 1000);

  ck_assert_str_eq(res1, res2);
}

TCase *memcpy_test() {
  TCase *tc = tcase_create("Memcpy test.");
  tcase_add_test(tc, test_memcpy);
  return tc;
}

START_TEST(test_memset) {
  char str1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char str2[BUFFER_SIZE] = "49492912941jfsa";

  void *res1 = s21_memset(str1, (int)'4', 10);
  void *res2 = memset(str2, (int)'4', 10);

  str1[10] = '\0';
  str2[10] = '\0';

  ck_assert_str_eq(res1, res2);

  res1 = s21_memset(str1, (int)'1', 100);
  res2 = memset(str2, (int)'1', 100);

  ck_assert_str_eq(res1, res2);
}

TCase *memset_test() {
  TCase *tc = tcase_create("Memset test.");
  tcase_add_test(tc, test_memset);
  return tc;
}

Suite *s21_mem_functions() {
  Suite *s = suite_create("Memory functions");
  suite_add_tcase(s, memchr_test());
  suite_add_tcase(s, memcmp_test());
  suite_add_tcase(s, memcpy_test());
  suite_add_tcase(s, memset_test());
  return s;
}

// String functions

START_TEST(test_strncat) {
  char dest1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char dest2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strncat(dest1, "fjsajf1204", 9);
  char *res2 = strncat(dest2, "fjsajf1204", 9);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strncat(dest1, "jfaskjr19324219jfasklfjvmxz", 15);
  res2 = strncat(dest2, "jfaskjr19324219jfasklfjvmxz", 15);

  ck_assert_str_eq(res1, res2);
}

TCase *strncat_test() {
  TCase *tc = tcase_create("Strncat test.");
  tcase_add_test(tc, test_strncat);
  return tc;
}

START_TEST(test_strchr) {
  char src1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strchr(src1, '@');
  char *res2 = strchr(src2, '@');

  ck_assert_str_eq(res1, res2);

  res1 = s21_strchr(src1, '.');
  res2 = strchr(src2, '.');

  ck_assert_ptr_eq(res1, res2);

  res1 = s21_strchr(src1, '4');
  res2 = strchr(src2, '4');

  ck_assert_str_eq(res1, res2);
}

TCase *strchr_test() {
  TCase *tc = tcase_create("Strchr test.");
  tcase_add_test(tc, test_strchr);
  return tc;
}

START_TEST(test_strncmp) {
  char src1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  int res1 = s21_strncmp(src1, src2, 10);
  int res2 = strncmp(src1, src2, 10);

  ck_assert_int_eq(res1, res2);

  src1[4] = '9';
  res1 = s21_strncmp(src1, src2, 10);
  res2 = strncmp(src1, src2, 10);

  ck_assert_int_eq(res1, res2);

  src1[4] = '0';
  res1 = s21_strncmp(src1, src2, 10);
  res2 = strncmp(src1, src2, 10);

  ck_assert_int_eq(res1, res2);
}

TCase *strncmp_test() {
  TCase *tc = tcase_create("Strncmp test.");
  tcase_add_test(tc, test_strncmp);
  return tc;
}

START_TEST(test_strncpy) {
  char dest1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src1[BUFFER_SIZE] = "1234949192jfafs";

  char dest2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src2[BUFFER_SIZE] = "1234949192jfafs";

  char *res1 = s21_strncpy(dest1, src1, 10);
  char *res2 = strncpy(dest2, src2, 10);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strncpy(dest1, src1, 1000);
  res2 = strncpy(dest2, src2, 1000);

  ck_assert_str_eq(res1, res2);
}

TCase *strncpy_test() {
  TCase *tc = tcase_create("Strncpy test.");
  tcase_add_test(tc, test_strncpy);
  return tc;
}

START_TEST(test_strcspn) {
  char dest[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char sym[BUFFER_SIZE] = "(@!00fs)";

  size_t res1 = s21_strcspn(dest, sym);
  size_t res2 = strcspn(dest, sym);

  ck_assert_int_eq(res1, res2);

  char sym1[BUFFER_SIZE] = ".";
  res1 = s21_strcspn(dest, sym1);
  res2 = strcspn(dest, sym1);

  ck_assert_int_eq(res1, res2);

  char sym2[BUFFER_SIZE] = "4";
  res1 = s21_strcspn(dest, sym2);
  res2 = strcspn(dest, sym2);

  ck_assert_int_eq(res1, res2);
}

TCase *strcspn_test() {
  TCase *tc = tcase_create("Strcspn test.");
  tcase_add_test(tc, test_strcspn);
  return tc;
}

START_TEST(test_strerror) {
  char *res1 = s21_strerror(14);
  char *res2 = strerror(14);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strerror(51);
  res2 = strerror(51);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strerror(100);
  res2 = strerror(100);

  ck_assert_str_eq(res1, res2);

#undef __linux__
#define __APPLE__

  res1 = s21_strerror(51);
  res2 = strerror(51);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strerror(100);
  res2 = strerror(100);

  ck_assert_str_eq(res1, res2);

  res1 = s21_strerror(1000);
  res2 = strerror(1000);
  ck_assert_str_eq(res1, res2);

  res1 = s21_strerror(-1000);
  res2 = strerror(-1000);

  ck_assert_str_eq(res1, res2);

#undef __APPLE__
#define __linux__
}

TCase *strerror_test() {
  TCase *tc = tcase_create("Strerror test.");
  tcase_add_test(tc, test_strerror);
  return tc;
}

START_TEST(test_strlen) {
  size_t res1 = s21_strlen("1249492");
  size_t res2 = strlen("1249492");

  ck_assert_int_eq(res1, res2);

  res1 = s21_strlen("");
  res2 = strlen("");

  ck_assert_int_eq(res1, res2);
}

TCase *strlen_test() {
  TCase *tc = tcase_create("Strlen test.");
  tcase_add_test(tc, test_strlen);
  return tc;
}

START_TEST(test_strpbrk) {
  char dest[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strpbrk(dest, "(@!)");
  char *res2 = strpbrk(dest, "(@!)");

  ck_assert_str_eq(res1, res2);

  res1 = s21_strpbrk(dest, "494912");
  res2 = strpbrk(dest, "494912");

  ck_assert_str_eq(res1, res2);

  res1 = s21_strpbrk(dest, "");
  res2 = strpbrk(dest, "");

  ck_assert_ptr_eq(res1, res2);
}

TCase *strpbrk_test() {
  TCase *tc = tcase_create("Strpbrk test.");
  tcase_add_test(tc, test_strpbrk);
  return tc;
}

START_TEST(test_strrchr) {
  char src[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strrchr(src, (int)'9');
  char *res2 = strrchr(src, (int)'9');

  ck_assert_str_eq(res1, res2);

  res1 = s21_strrchr(src, 'a');
  res2 = s21_strrchr(src, 'a');

  ck_assert_str_eq(res1, res2);
}

TCase *strrchr_test() {
  TCase *tc = tcase_create("Strrchr test.");
  tcase_add_test(tc, test_strrchr);
  return tc;
}

START_TEST(test_strstr) {
  char haystack[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strstr(haystack, "12139");
  char *res2 = strstr(haystack, "12139");

  ck_assert_str_eq(res1, res2);

  res1 = s21_strstr(haystack, "129391");
  res2 = strstr(haystack, "129391");

  ck_assert_ptr_eq(res1, res2);

  res1 = s21_strstr(haystack, "1");
  res2 = strstr(haystack, "1");

  ck_assert_str_eq(res1, res2);
}

TCase *strstr_test() {
  TCase *tc = tcase_create("Strstr test.");
  tcase_add_test(tc, test_strstr);
  return tc;
}

START_TEST(test_strtok) {
  char src1[BUFFER_SIZE] = "49492912139(@(!())00fsja)";
  char src2[BUFFER_SIZE] = "49492912139(@(!())00fsja)";

  char *res1 = s21_strtok(src1, "(0)");
  char *res2 = strtok(src2, "(0)");

  while (res2 != NULL) {
    ck_assert_str_eq(res1, res2);
    res1 = s21_strtok(NULL, "(0)");
    res2 = strtok(NULL, "(0)");
  }

  res1 = s21_strtok(src1, "");
  res2 = s21_strtok(src2, "");

  while (res2 != NULL) {
    ck_assert_str_eq(res1, res2);
    res1 = s21_strtok(NULL, "(0)");
    res2 = strtok(NULL, "(0)");
  }
}

TCase *strtok_test() {
  TCase *tc = tcase_create("Strtok test.");
  tcase_add_test(tc, test_strtok);
  return tc;
}

Suite *s21_str_functions() {
  Suite *s = suite_create("String functions");
  suite_add_tcase(s, strncat_test());
  suite_add_tcase(s, strchr_test());
  suite_add_tcase(s, strncmp_test());
  suite_add_tcase(s, strncpy_test());
  suite_add_tcase(s, strcspn_test());
  suite_add_tcase(s, strerror_test());
  suite_add_tcase(s, strlen_test());
  suite_add_tcase(s, strpbrk_test());
  suite_add_tcase(s, strrchr_test());
  suite_add_tcase(s, strstr_test());
  suite_add_tcase(s, strtok_test());
  return s;
}

// String Processing Tests

START_TEST(test_to_upper) {
  char *res = s21_to_upper("fasfas");
  ck_assert_str_eq(res, "FASFAS");
  free(res);
  res = s21_to_upper("");
  ck_assert_str_eq(res, "");
  free(res);
  res = s21_to_upper("!231420jfnvzжж");
  ck_assert_str_eq(res, "!231420JFNVZжж");
  free(res);
}

TCase *to_upper_test() {
  TCase *tc = tcase_create("To upper test.");
  tcase_add_test(tc, test_to_upper);
  return tc;
}

START_TEST(test_to_lower) {
  char *res = s21_to_lower("FAJAJSFJ");
  ck_assert_str_eq(res, "fajajsfj");
  free(res);
  res = s21_to_lower("");
  ck_assert_str_eq(res, "");
  free(res);
  res = s21_to_lower("FAJAJSFJvzx1123");
  ck_assert_str_eq(res, "fajajsfjvzx1123");
  free(res);
}

TCase *to_lower_test() {
  TCase *tc = tcase_create("To lower test.");
  tcase_add_test(tc, test_to_lower);
  return tc;
}

START_TEST(test_to_insert) {
  char str[BUFFER_SIZE] = "hello 1234123, 1230";
  char *res = s21_insert(str, "hello", 4);
  ck_assert_str_eq(res, "hellhelloo 1234123, 1230");
  free(res);

  res = s21_insert(str, ".,/zxxmvxz", 10);
  ck_assert_str_eq(res, "hello 1234.,/zxxmvxz123, 1230");
  free(res);
}

TCase *insert_test() {
  TCase *tc = tcase_create("To insert test.");
  tcase_add_test(tc, test_to_insert);
  return tc;
}

START_TEST(test_to_trim) {
  char str[BUFFER_SIZE] = "l hello 1234123, 1230";
  char *res = s21_trim(str, "l1230");
  ck_assert_str_eq(res, " hello 1234123, ");
  free(res);
}

TCase *trim_test() {
  TCase *tc = tcase_create("To trim test.");
  tcase_add_test(tc, test_to_trim);
  return tc;
}

Suite *s21_str_processing_functions() {
  Suite *s = suite_create("String processing functions");
  suite_add_tcase(s, to_upper_test());
  suite_add_tcase(s, to_lower_test());
  suite_add_tcase(s, insert_test());
  suite_add_tcase(s, trim_test());
  return s;
}

int main() {
  int number_failed = 0;
  Suite *string_tests[] = {
      s21_sprintf_suite(),
      s21_sscanf_suite(),
      s21_mem_functions(),
      s21_str_functions(),
      s21_str_processing_functions(),
      NULL,
  };

  for (int i = 0; string_tests[i]; i++) {
    SRunner *srunner;
    srunner = srunner_create(string_tests[i]);
    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_VERBOSE);
    number_failed += srunner_ntests_failed(srunner);
    srunner_free(srunner);
  }

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
