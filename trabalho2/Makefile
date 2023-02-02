CC = g++ -g

OBJS = grafo.o Data.o main.o
EXE  = escalona

CFLAGS = -Wall
LDLIBS = -lcgraph

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS) $(LDLIBS)

Data.o: Data.cpp Data.hpp
	$(CC) -c $< $(CFLAGS)

main.o: main.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	@ rm -f $(EXE) $(OBJS)

.PHONY: all clean
