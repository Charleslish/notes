# Write the rules for this project here. Every recipe line begins with a tab.
# make reads this file; nothing else does.
CXX = clang++
CXX_FLAGS = -std=c++20 -I ./includes -Wall -Wextra -Werror -pedantic \
            -fsanitize=address,undefined -fno-sanitize-recover=all -g -O0
TEST_FLAGS = -std=c++20 -stdlib=libc++ -Wall -Wextra -Werror -pedantic \
             -I ./includes -g -O0

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/tiles.cc ./includes/tiles.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/tiles.cc -o $@
bin/tests: ./tests/tests.cc ./src/tiles.cc ./includes/tiles.hpp
	$(CXX) $(TEST_FLAGS) ./tests/tests.cc ./src/tiles.cc -o $@ -lCatch2Main -lCatch2

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
	rm -f bin/*