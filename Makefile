CC=g++
CFLAGS=-g -Wall -O0
BIN=isoclient

isoclient: isoclient.cc
	$(CC) $(CFLAGS) isoclient.cc -o $@

all: $(BIN)

clean:
	@rm -f ./*.o $(BIN)

