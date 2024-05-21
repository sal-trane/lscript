CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=build/lib/errors.o build/lib/parser.o build/lib/progheap.o build/lib/util.o
TESTS=build/tests/test_memory_usage build/tests/test_parser_atoms build/tests/test_parser_collections
.PHONY: test
.PRECIOUS: build/lib/%.o

build:
	mkdir -p build/lib

build/tests: build
	mkdir -p build/tests

build/lib/%.o: lib/%.c build
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/%: tests/%.c build/tests $(OBJS)
	$(CC) $(CLFAGS) -Ilib -o $@ $< $(OBJS)

test: $(TESTS)
	$(foreach TEST,$(TESTS), echo "$(TEST)" && ./$(TEST) &&) true
