CC=g++
CFLAGS=-g -std=c++11 -Wall -Wno-write-strings -O0 -I./include -DLOG_USE_COLOR

OBJS=obj/log.o

bin/isoclient: src/isoclient.cc $(OBJS)
	$(CC) $(CFLAGS) -c src/isoclient.cc -o obj/isoclient.o
	$(CC) $(CFLAGS) $(OBJS) obj/isoclient.o -o $@

obj/log.o: src/log.cc
	$(CC) $(CFLAGS) -c src/log.cc -o $@

test: tests/main.cc include/snow.h
	$(CC) $(CFLAGS) tests/main.cc -o bin/tests
	bin/tests

clean:
	@rm -f obj/*.o bin/*

