CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wno-unused-private-field $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/driver.cc src/order_bst.cc src/order_book.cc src/utilities.cc includes/order_bst.hpp includes/order_book.hpp includes/tnode.hpp includes/utilities.hpp
	${CXX} ${CXX_FLAGS} src/driver.cc src/order_bst.cc src/order_book.cc src/utilities.cc -o bin/exec

bin/tests: tests/tests.cc src/order_bst.cc src/order_book.cc src/utilities.cc includes/order_bst.hpp includes/order_book.hpp includes/tnode.hpp includes/utilities.hpp
	${CXX} ${CXX_FLAGS} -Itests/ tests/tests.cc src/order_bst.cc src/order_book.cc src/utilities.cc -lCatch2Main -lCatch2 -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
