#!/usr/bin/make

CC = g++
SRC = driver.cpp PatternMatcher.cpp
PROG = pmatcher.out

run: build
	./$(PROG)

build: clean $(PROG)

clean:
	rm -f $(PROG)

$(PROG): $(SRC)
	$(CC) $(SRC) -o $(PROG)
