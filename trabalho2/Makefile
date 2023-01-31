CC = g++

OBJS = grafo.o Data.o main.o
EXE  = main

CFLAGS = -Wall
LDLIBS = -lcgraph

all: $(EXE)

main: $(OBJS)
	$(CC) -o teste $(OBJS) $(CFLAGS) $(LDLIBS)

Data.o: Data.cpp Data.hpp
	$(CC) -c $< $(CFLAGS)

main.o: main.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	@ rm -f $(EXE) $(OBJS)

.PHONY: all clean
