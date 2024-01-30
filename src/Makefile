CC = g++
CFLAGS = -arch arm64 -Wall -Werror -Wextra -std=c++17 $(shell pkg-config --cflags gtest)
TFLAGS = $(shell pkg-config --libs gtest)
OBJECTS = s21_containers.o
SOURCE_DEC = tests/*.cpp

all: test

#s21_containers.a:
#	$(CC) $(CFLAGS) -c $(SOURCE_DEC)
#	ar rcs $(LIB) $(OBJECTS)
#	ranlib $(LIB)
#	rm *.o
clean:
	rm -rf *.o *.a *.out test test_output

test: clean
	@$(CC) $(CFLAGS) tests/*.cpp $(TFLAGS) -o test
	@./test

rebuild:
	$(MAKE) clean
	$(MAKE) all

check_style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

leaks:
	leaks -atExit -- ./test