CC=g++
CFLAGS=-g -std=c++11 -Wall -Wno-write-strings -O0 -I./include -DLOG_USE_COLOR

OBJS=obj/log.o
TESTOBJS=obj/dummy.o

bin/isoclient: src/isoclient.cc $(OBJS)
	$(CC) $(CFLAGS) -c src/isoclient.cc -o obj/isoclient.o
	$(CC) $(CFLAGS) $(OBJS) obj/isoclient.o -o $@

obj/log.o: src/log.cc
	$(CC) $(CFLAGS) -c src/log.cc -o $@

obj/dummy.o: tests/dummy.cc
	$(CC) $(CFLAGS) -c tests/dummy.cc -o $@

test: tests/main.cc $(TESTOBJS)
	$(CC) $(CFLAGS) -c tests/main.cc -o obj/main.o
	$(CC) $(CFLAGS) $(TESTOBJS) obj/main.o -o bin/tests
	@bin/tests

clean:
	@rm -f obj/*.o bin/*

