CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SF = -fsanitize=leak,address

ifeq ($(shell uname), Linux)
    all: s21_decimal.a test gcov_report

    s21_decimal.a: *.c s21_arithmetic/*.c s21_another/*.c s21_convertors/*.c s21_comparisons/*.c s21_decimal.h
		$(CC) $(CFLAGS) -c *.c s21_arithmetic/*.c s21_another/*.c s21_convertors/*.c s21_comparisons/*.c
		ar rcs $@ *.o
		ranlib s21_decimal.a

    test: s21_decimal.a
		$(CC) -g $(CFLAGS) -fprofile-arcs -ftest-coverage -o ./s21_test/s21test s21_test/*.c *.c s21_arithmetic/*.c s21_another/*.c s21_convertors/*.c s21_comparisons/*.c s21_decimal.h -lcheck -lm -lsubunit

    gcov_report: test
		chmod +x ./s21_test/s21test && ./s21_test/s21test
		mkdir -p gcov-report
		gcovr -r . --html --html-details -o gcov-report/index.html
		open ./gcov-report/index.html

else ifeq ($(shell uname), Darwin)
    SOURCES=$(wildcard s21_test/*.c functions/*.c)
    OBJECTS=$(SOURCES:.c=.o)
    all: s21_decimal.a test gcov_report
    
    s21_decimal.a: *.c s21_arithmetic/*.c s21_another/*.c s21_convertors/*.c s21_comparisons/*.c
		$(CC) $(CFLAGS)  -c *.c s21_arithmetic/*.c s21_another/*.c s21_convertors/*.c s21_comparisons/*.c
		ar rc s21_decimal.a *.o
		ranlib s21_decimal.a

    $(OBJECTS): %.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@

    test: $(OBJECTS) s21_decimal.a
		$(CC) -g $(CFLAGS) -fprofile-arcs -ftest-coverage -o ./s21test $^ -lcheck -lm

    gcov_report: test
		$(CC) --coverage $(CFLAGS) -o s21test *.c  ./s21_arithmetic/*.c ./s21_another/*.c ./s21_convertors/*.c ./s21_comparisons/*.c ./s21_test/*.c -lcheck
		chmod +x ./s21test && ./s21test
		lcov -t "s21test" -o s21test.info -c -d .
		genhtml -o gcov-report s21test.info
		open ./gcov-report/index.html

    lib:
		brew install check
		brew install lcov
endif

clean:
	rm -rf *.o *.a s21_test/*.gcno s21_test/*.gcda s21_test/s21test
	rm -r gcov-report *.info s21_another/*.o s21_arithmetic/*.o s21_convertors/*.o s21_comparisons/*.o s21_test/*.o

rebuild: clean all