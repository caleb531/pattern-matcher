#!/usr/bin/make

CC = g++
SRC = pattern-matcher.cpp
PROG = pattern-matcher.out

build: clean $(PROG)

clean:
	rm -f $(PROG)

$(PROG): $(SRC)
	$(CC) $(SRC) -o $(PROG)
