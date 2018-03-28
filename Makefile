CC=g++
CFLAGS=-g -std=c++11 -Wall -Wno-write-strings -O0 -I./include

bin/isoclient: src/isoclient.cc
	$(CC) $(CFLAGS) src/isoclient.cc -o $@

test: tests/main.cc include/snow.h
	$(CC) $(CFLAGS) tests/main.cc -o bin/tests

clean:
	@rm -f obj/*.o bin/*

