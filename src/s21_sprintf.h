#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool left_justify;
  bool with_sign;
  bool space;
  bool hash;
  bool set_zeroes;

  size_t width;
  size_t precision;
  bool precision_set;

  char length;
  char specifier;
} options;

#define ZERO_NUMBER_IN_ASCII 48
#define NINE_NUMBER_IN_ASCII 57

int s21_sprintf(char *str, const char *format, ...);
void handle_specifier(va_list args, options opts, char *dest, size_t *curr);

bool get_flag(options *opts, char *ptr);
char *get_width(va_list args, options *opts, char *ptr);
char *get_precision(va_list args, options *opts, char *ptr);
char *get_length(options *opts, char *ptr);

void parse_int(va_list args, options opts, char *buffer);
void parse_char(va_list args, options opts, char *dest);
void parse_string(va_list args, options opts, char *dest);
void parse_unsigned_int(va_list args, options opts, char *dest);
void parse_float(va_list args, options opts, char *dest);

void add_int_to_string(char *dest, options opts, size_t chars_length,
                       size_t num_length, size_t zeroes_for_add, long num,
                       char *num_str);
void add_unsigned_int_to_string(char *dest, options opts, size_t chars_length,
                                size_t num_length, size_t zeroes_for_add,
                                char *num_str);
void add_double_to_string(char *dest, options opts, size_t chars_length,
                          size_t num_length, size_t zeroes_for_add, double num,
                          char *num_str);

void parse_double_to_str(char *dest, double num, int decimal_places);

int parse_int_from_ascii(char **str);
void parse_int_to_ascii(long num, int base, char *dest);