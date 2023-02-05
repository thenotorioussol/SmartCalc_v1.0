CC=gcc
SRC=calclib/calc.c calclib/parser.c calclib/stack.c banklib/credit.c banklib/deposit.c
SRC_T=tests/tests.c tests/tests_calc.c tests/tests_credit.c tests/tests_deposite.c
OBJ=calclib/calc.o calclib/parser.o calclib/stack.o banklib/credit.o banklib/deposit.o
OBJ_T=tests/tests.o tests/tests_calc.o tests/tests_credit.o tests/tests_deposite.o
CFLAGS=-Wall -Werror -Wextra --coverage
TESTFLAGS=-lcheck -lm -lpthread -lgcov -lsubunit

detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')

all: tests dist install go

gcov_report: tests
	gcovr -r. --html --html-details -o report/coverage_report.html

tests: lib.a $(OBJ_T) $(OBJ)
	$(CC) $(CFLAGS) lib.a $(OBJ_T) $(OBJ) $(TESTFLAGS) -o test
	valgrind ./test

lib.a: $(OBJ)
	ar rcs lib.a $(OBJ)

install:
	cmake CMakeLists.txt
	make
	rm -rf Makefile
	cp MFile/Makefile .

ifeq ($(detected_OS),Linux)
go:
	./SmartCalc_v1.0
endif
ifeq ($(detected_OS),Darwin)
go:
	./SmartCalc_v1.0.app/Contents/MacOS/SmartCalc_v1.0
endif

dist:
	tar czf dist.tar calclib/* banklib/* gnu/* CMakeLists.txt Makefile

dvi:
	open doc/dvi.txt

uninstall:
	rm -rf SmartCalc_v1.0
	rm -rf SmartCalc_v1.0.app
	rm -rf SmartCalc_v1.0_autogen
	rm -rf CMakeFiles
	rm -rf cmake_install.cmake
	rm -rf CMakeCache.txt
	
clean:
	rm -rf */*.o 
	rm -rf */*.gc*
	rm -rf *.a
	rm test
	rm -rf a.out *.a
	rm -rf dist.tar