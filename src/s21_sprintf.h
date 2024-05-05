#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

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
#define BUFFER_SIZE 4096

int s21_sprintf(char *str, const char *format, ...);
void handle_specifier(va_list args, options opts, char *dest, size_t *curr);

bool get_flag(options *opts, char *ptr);
char *get_width(va_list args, options *opts, char *ptr);
char *get_precision(va_list args, options *opts, char *ptr);
char *get_length(options *opts, char *ptr);

void parse_int(va_list args, options opts, char *buffer);
void add_int_to_string(char *dest, options opts, size_t chars_length, size_t num_length, size_t zeroes_for_add, long num, char *num_str);

int parse_int_from_ascii(char **str);
void parse_int_to_ascii(long num, int base, char *dest);