CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fsanitize=address -Wall -Wextra -pedantic -Wno-error=unused $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./includes/dna_strand.hpp ./src/dna_strand.cc ./includes/node.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/dna_strand.cc  -o $@

bin/tests: obj/catch_main.o ./tests/tests.cc ./includes/dna_strand.hpp ./src/dna_strand.cc ./includes/node.hpp
	$(CXX) $(CXXFLAGS) obj/catch_main.o ./tests/tests.cc ./src/dna_strand.cc -o $@

obj/catch_main.o: ./tests/catch.cc ./tests/catch.hpp
	$(CXX) $(CXX_FLAGS) -c ./tests/catch.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
