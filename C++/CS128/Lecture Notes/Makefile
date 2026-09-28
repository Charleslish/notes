CXX = clang++

CXXFLAGS = -std=c++20 -I ./includes \
           -Wall -Wextra -Werror -pedantic \
           -Wno-error=unused-parameter \
           -g -O0 \
           -fsanitize=address,undefined,implicit-conversion,local-bounds

TEST_FLAGS = -std=c++20 -stdlib=libc++ \
             -I ./includes \
             -Wall -Wextra -Werror -pedantic \
             -g -O0

SOURCES := $(wildcard src/*.cc)
HEADERS := $(wildcard includes/*.hpp)

TARGET := bin/exec
TEST_TARGET := bin/tests

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

exec: $(TARGET)

tests: $(TEST_TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

$(TEST_TARGET): tests/tests.cc src/solution.cc $(HEADERS)
	@mkdir -p bin
	$(CXX) $(TEST_FLAGS) tests/tests.cc src/solution.cc -o $@ -lCatch2Main -lCatch2

clean:
	rm -f bin/*