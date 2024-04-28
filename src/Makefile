CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
SRC = s21_*.c


all: clean s21_string.a test

s21_string.a:
	$(CC) $(FLAGS) -c $(SRC)
	ar -rc s21_string.a *.o

test:
	$(CC) $(FLAGS) test.c s21_string.a

clean:
	rm -rf *.o *.a *.out