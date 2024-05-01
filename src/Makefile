CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
ODIR = objs
CDIR = .

SOURCES = $(wildcard $(CDIR)/s21_*.c)
OBJECTS = $(patsubst $(CDIR)/%.c,$(ODIR)/%.o,$(SOURCES))

.PHONY: all clean test

all: clean s21_string.a test

$(ODIR)/%.o: $(CDIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

s21_string.a: $(OBJECTS)
	ar -rc s21_string.a $(OBJECTS)

test: s21_string.a
	$(CC) $(FLAGS) test.c s21_string.a

clean:
	rm -rf $(OBJECTS)/*.o *.a *.out