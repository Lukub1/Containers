FLAGS = -lgtest -lstdc++ -std=c++20
WWW = -Wall -Wextra -Werror

all: test report 

test:
	g++  s21_test.cc  s21_containers.h -o   test $(WWW) $(FLAGS)
	./test

report:
	g++ --coverage -fprofile-arcs -ftest-coverage  s21_test.cc $(FLAGS) -o test -lgtest 
	@./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

style: 
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.tpp *.h
	@rm .clang-format

clean: 
	rm -rf *.o *.gch *.out *.a report *.info *.gc* test
