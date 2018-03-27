CC=g++
CFLAGS=-g -Wall -O0

client: client.cc
	$(CC) $(CFLAGS) client.cc -o $@

all: client

clean:
	@rm -f ./*.o
