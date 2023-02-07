FLAGS = -Wall -Werror -Wextra -std=c11

SRC = s21_cat.c
OBJ = s21_cat a.out a b res

all: clean build

build: s21_cat

test: s21_cat
	python3 test_cat.py

style:
	cppcheck *.h *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h

s21_cat: s21_cat.c
	gcc $(FLAGS) $(SRC) -o s21_cat

.PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -rf CPPLINT.cfg
