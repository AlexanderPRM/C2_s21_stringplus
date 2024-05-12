#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#define spec_unknown '?'

#define LENGTH_h 0x00000001
#define LENGTH_l 0x00000002
#define LENGTH_L 0x00000004
#define LENGTH_none 0x00000008

typedef struct {
  bool skip;
  int width;
  int length;
  char specifier;
} specifier;

int s21_sscanf(const char *str, const char *format, ...);

int s21_remove_extra(const char *str);
specifier s21_scan_spec(const char **symbol);
void s21_set_value(int *result, va_list arguments, specifier spec,
                   char **string, const char *str, const char **format,
                   bool *should_break);

bool s21_is_digit(const char symbol, int base);
size_t s21_to_digit(const char symbol, int base);

bool s21_is_hex_prefix(char **string, int width);
int s21_spec_x_o_d(specifier spec, va_list arguments, char **string,
                   int number_system, bool negative, bool *should_break);

int s21_spec_u(specifier spec, va_list arguments, char **string,
               bool *should_break);
int s21_parse_based_uint(specifier spec, char **string, va_list arguments,
                         bool is_negative, int base);
bool s21_scan_based_uint(unsigned long long *result, char **string, int width,
                         bool is_negative, int base, specifier spec);

void s21_spec_percent(char **string, const char **format, int *result,
                      bool *should_break);
int s21_spec_i(specifier spec, va_list arguments, char **string,
               bool *should_break);
int s21_spec_c_s(specifier spec, va_list arguments, char **string);

int s21_spec_f_e_g(specifier spec, va_list arguments, char **string);
int s21_scan_float(long double *number, char **string, int width);
bool s21_is_nan_or_inf(char **string, long double *result);
bool s21_strstr_sscanf(char **str, char *pat);
char s21_to_lower_sscanf(char c);
long double s21_atof(char **string, int *width);
void s21_scientific(long double *result, char **string, int *width);
void s21_scan_int(char **string, int *width, long long *result);

#endif