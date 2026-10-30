CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fsanitize=address -O0
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -Wno-error=unused-parameter

exec: bin/exec
tests: bin/tests

bin/exec : ./includes/db.hpp ./src/db.cc ./includes/db_table.hpp ./src/db_table.cc ./src/driver.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/db.cc ./src/db_table.cc ./src/driver.cc -o ./bin/exec

obj/catch_main.o: ./tests/catch_main.cc
	$(CXX) $(CXX_FLAGS) -c ./tests/catch_main.cc -o $@

bin/tests : ./includes/db.hpp ./src/db.cc ./includes/db_table.hpp ./src/db_table.cc ./tests/tests.cc ./obj/catch_main.o
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./obj/catch_main.o ./src/db.cc ./src/db_table.cc ./tests/tests.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
