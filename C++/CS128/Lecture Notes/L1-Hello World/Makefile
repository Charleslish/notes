CXX = clang++

CXXFLAGS = -std=c++20 -Iincludes \
           -Wall -Wextra -pedantic \
           -Wno-error=unused-parameter \
           -g -O0 \
           -fsanitize=address,undefined,implicit-conversion,local-bounds

SOURCES := $(wildcard src/*.cc)

TARGET := bin/exec

exec: $(TARGET)

$(TARGET): $(SOURCES) $(wildcard includes/*.hpp)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

.DEFAULT_GOAL := exec

.PHONY: exec clean

clean:
	rm -rf bin/*