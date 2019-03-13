CC=gcc
CFLAGS=-g -std=c11 -Wall -Wno-write-strings -O0 -I./include

TESTOBJS=obj/dummy.o obj/bitops_suite.o

zf_log: src/zf_log.c
	$(CC) $(CFLAGS) 

bin/isoclient: src/main.c
	$(CC) $(CFLAGS) -c $< -o obj/isoclient.o
	$(CC) $(CFLAGS) obj/isoclient.o -o $@ $(LIBS)

clean:
	@rm -f obj/*.o bin/isoclient

