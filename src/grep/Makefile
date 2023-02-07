FLAGS = -Wall -Werror -Wextra -std=c11 -pedantic

SRC = s21_grep.c
OBJ = s21_grep a.out a b res

all: build

re: clean build

build: s21_grep

test: s21_grep
	python3 test_grep.py

docker:
	sh ../../materials/build/run.sh

style:
	cppcheck *.h *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h

s21_grep: s21_grep.c
	gcc $(FLAGS) $(SRC) -o s21_grep

.PHONY: clean

clean:
	rm -rf $(OBJ) CPPLINT.cfg
