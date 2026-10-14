CXX := clang++
CPPFLAGS := -Iincludes -Ivendor/zlib
CXXFLAGS := -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -Werror -pedantic -g -O0
SANITIZERS := -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer
CATCH_CFLAGS := $(shell pkg-config --cflags catch2-with-main 2>/dev/null)
CATCH_LIBS := $(shell pkg-config --libs catch2-with-main 2>/dev/null || echo -lCatch2Main -lCatch2)
ZLIB_LIBS := -lz
ifeq ($(shell uname -s),Linux)
ZLIB_LIBS := -l:libz.so.1
endif
COMMON := src/image.cc src/seam_carver.cc src/pixel.cc src/png_io.cc
HEADERS := $(wildcard includes/*.hpp)

.PHONY: all exec tests fixtures check tidy clean
all: exec
exec: bin/exec
tests: bin/tests
fixtures: bin/make_fixture

bin:
	mkdir -p bin

bin/exec: src/driver.cc src/utilities.cc $(COMMON) $(HEADERS) | bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANITIZERS) src/driver.cc src/utilities.cc $(COMMON) $(ZLIB_LIBS) -o $@

bin/tests: $(wildcard tests/*.cc) examples/sample_tests.cc $(COMMON) $(HEADERS) | bin
	$(CXX) $(CPPFLAGS) $(CATCH_CFLAGS) $(CXXFLAGS) $(SANITIZERS) $(wildcard tests/*.cc) examples/sample_tests.cc $(COMMON) $(CATCH_LIBS) $(ZLIB_LIBS) -o $@

bin/make_fixture: examples/make_fixture.cc src/image.cc src/pixel.cc src/png_io.cc $(HEADERS) | bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANITIZERS) examples/make_fixture.cc src/image.cc src/pixel.cc src/png_io.cc $(ZLIB_LIBS) -o $@

check: bin/tests
	bin/tests

tidy:
	clang-tidy src/pixel.cc src/image.cc src/seam_carver.cc -- $(CPPFLAGS) -std=c++20

clean:
	$(RM) bin/exec bin/tests bin/make_fixture
