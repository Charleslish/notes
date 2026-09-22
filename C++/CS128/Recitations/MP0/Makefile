CXX=clang++
CXXFLAGS=-std=c++20 -Iincludes -Wall -Wextra -pedantic -Wno-error=unused-parameter -g -O0 -fsanitize=address,undefined,implicit-conversion,local-bounds

exec: bin/exec

bin/exec: ./src/driver.cc ./src/solution.cc ./includes/solution.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/solution.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*
