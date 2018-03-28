CC=g++
CFLAGS=-g -Wall -O0

bin/isoclient: src/isoclient.cc
	$(CC) $(CFLAGS) src/isoclient.cc -o $@

clean:
	@rm -f ./*.o bin/*

