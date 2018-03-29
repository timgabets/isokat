CC=g++
CFLAGS=-g -std=c++11 -Wall -Wno-write-strings -O0 -I./include -I/usr/include/libxml2 -DLOG_USE_COLOR
LIBS=-lxml2

OBJS=obj/log.o
TESTOBJS=obj/dummy.o obj/bitops_suite.o

bin/isoclient: src/isoclient.cc $(OBJS)
	$(CC) $(CFLAGS) -c $< -o obj/isoclient.o $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) obj/isoclient.o -o $@ $(LIBS)

obj/log.o: src/log.cc
	$(CC) $(CFLAGS) -c $< -o $@

obj/dummy.o: tests/dummy.cc
	$(CC) $(CFLAGS) -c $< -o $@

obj/bitops_suite.o: tests/bitops_suite.cc
	$(CC) $(CFLAGS) -c $< -o $@

test: tests/main.cc $(TESTOBJS)
	$(CC) $(CFLAGS) -c $< -o obj/main.o
	$(CC) $(CFLAGS) $(TESTOBJS) obj/main.o -o bin/tests
	@bin/tests

clean:
	@rm -f obj/*.o bin/isoclient

