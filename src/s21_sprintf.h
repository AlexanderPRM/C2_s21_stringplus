#include <stdarg.h>
#include <stdbool.h>

typedef struct {
  bool left_justify;
  bool with_sign;
  bool space;
  bool hash;
  bool set_zeroes;

  int width;
  int precision;
  bool precision_set;

  char length;
  char specifier;
} options;

#define ZERO_NUMBER_IN_ASCII 48
#define NINE_NUMBER_IN_ASCII 57

int s21_sprintf(char *str, const char *format, ...);

bool get_flag(options *opts, char *ptr);
char *get_width(va_list args, options *opts, char *ptr);
char *get_precision(va_list args, options *opts, char *ptr);
char *get_length(options *opts, char *ptr);

int parse_num_from_ascii(char **str);