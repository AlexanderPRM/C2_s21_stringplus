CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
ODIR = objs
CDIR = .
LIBRARY=s21_string.a
TEST_OUT=./test

SOURCES = $(wildcard $(CDIR)/s21_*.c)
OBJECTS = $(patsubst $(CDIR)/%.c,$(ODIR)/%.o,$(SOURCES))

.PHONY: all clean test

all: clean s21_string.a test

$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

s21_string.a: $(OBJECTS)
	ar -rc $(LIBRARY) $(OBJECTS)
	ranlib $(LIBRARY)
	rm -rf $(OBJECTS)

test: fclean s21_string.a
	$(CC) $(FLAGS) -o test test.c s21_string.a -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage
	./test
	

clean:
	rm -rf $(OBJECTS)/*.o *.a *.out

fclean:
	rm -rf $(TEST_OUT)
	rm -rf *.gcda *.gcno