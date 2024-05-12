CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
ODIR = objs
CDIR = .
LIBRARY=s21_string.a
TEST_OUT=./test

SOURCES = $(wildcard $(CDIR)/s21_*.c)
OBJECTS = $(patsubst $(CDIR)/%.c,$(ODIR)/%.o,$(SOURCES))

TST_LIBS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage


.PHONY: all clean test gcov_report

all: clean s21_string.a

$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

s21_string.a: $(OBJECTS)
	ar -rc $(LIBRARY) $(OBJECTS)
	ranlib $(LIBRARY)
	rm -rf $(OBJECTS)

test: fclean s21_string.a
	$(CC) $(FLAGS) -o test test.c s21_string.a -lcheck -lm -lsubunit
	./test

gcov_report: fclean s21_string.a
	$(CC) $(FLAGS) $(GCOVFLAGS) test.c s21_*.c s21_string.a -o report.out $(TST_LIBS)
	./report.out
	lcov -t "report" -o report.info -c -d .
	genhtml -o ./report report.info

local: clean s21_string.a
	$(CC) $(FLAGS) local.c s21_string.a -lm


clean:
	rm -rf $(OBJECTS)/*.o *.a *.out

fclean:
	rm -rf $(TEST_OUT)
	rm -rf *.gcda *.gcno