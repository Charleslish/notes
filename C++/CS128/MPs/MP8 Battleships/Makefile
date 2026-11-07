CXX := clang++
CPPFLAGS := -Iincludes
CXXFLAGS := -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -Werror -pedantic -g -O0
SANITIZERS := -fsanitize=address,undefined -fno-sanitize-recover=all
CATCH_CFLAGS := $(shell pkg-config --cflags catch2-with-main 2>/dev/null)
CATCH_LIBS := $(shell pkg-config --libs catch2-with-main 2>/dev/null || echo -lCatch2Main -lCatch2)
COMMON := src/ship.cc src/board.cc src/utilities.cc
HEADERS := $(wildcard includes/*.hpp)
MACHINE := $(if $(filter Linux,$(shell uname -s)),$(shell uname -m),$(shell uname -s) $(shell uname -m))
GAME_OBJ_aarch64 := vendor/game-aarch64.o
GAME_OBJ_arm64 := vendor/game-aarch64.o
GAME_OBJ_x86_64 := vendor/game-x86_64.o
GAME_OBJ_amd64 := vendor/game-x86_64.o
GAME_OBJ := $(GAME_OBJ_$(MACHINE))
NO_GAME := make play: no game object for this machine ($(MACHINE)); run make play inside the CS 128 dev container.

.PHONY: all exec tests check play tidy clean
all: tests
exec: bin/exec
tests: bin/tests

bin:
	mkdir -p bin

bin/exec: src/driver.cc $(COMMON) $(HEADERS) Makefile | bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANITIZERS) src/driver.cc $(COMMON) -o $@

bin/tests: $(wildcard tests/*.cc) examples/sample_tests.cc $(COMMON) $(HEADERS) Makefile | bin
	$(CXX) $(CPPFLAGS) $(CATCH_CFLAGS) $(CXXFLAGS) $(SANITIZERS) $(wildcard tests/*.cc) examples/sample_tests.cc $(COMMON) $(CATCH_LIBS) -o $@

check: bin/tests
	bin/tests

play: bin/play
	./bin/play $(if $(SEED),--seed $(SEED))

ifeq ($(wildcard $(GAME_OBJ)),)
bin/play:
	@echo "$(NO_GAME)"; exit 1
else
bin/play: $(GAME_OBJ) $(COMMON) src/layout.cc $(HEADERS) Makefile | bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANITIZERS) $(GAME_OBJ) $(COMMON) src/layout.cc -o $@
endif

tidy:
	clang-tidy src/ship.cc src/board.cc -- $(CPPFLAGS) -std=c++20

clean:
	$(RM) bin/exec bin/play bin/tests
