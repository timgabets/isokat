CC=gcc
CFLAGS=-g -std=c11 -Wall -Wno-write-strings -O0 -I./include

TESTOBJS=obj/dummy.o obj/bitops_suite.o

bin/isoclient: src/main.c
	$(CC) $(CFLAGS) -c $< -o obj/isoclient.o $(LIBS)
	$(CC) $(CFLAGS) obj/isoclient.o -o $@ $(LIBS)

clean:
	@rm -f obj/*.o bin/isoclient

