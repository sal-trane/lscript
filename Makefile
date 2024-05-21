CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=build/lib/errors.o build/lib/parser.o build/lib/progheap.o build/lib/util.o

build:
	mkdir -p build/lib

build/tests: build
	mkdir -p build/tests

build/lib/%.o: lib/%.c build
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/%: tests/%.c build/tests $(OBJS)
	$(CC) $(CLFAGS) -Ilib -o $@ $< $(OBJS)
