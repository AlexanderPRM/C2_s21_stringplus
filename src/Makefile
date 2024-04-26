CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
SRC = s21_*.c


all: clean s21_string.a test

s21_string.a:
	$(CC) $(FLAGS) -c $(SRC)
	ar -rc s21_string.a *.o

test:
	echo "TODO: run tests"

clean:
	rm -rf *.o *.a *.out