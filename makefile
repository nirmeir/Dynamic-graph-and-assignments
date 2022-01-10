CC=gcc
FLAGS= -Wall -g

all:graph


graph: main.o graph.o tsp.o
	$(CC) $(FLAGS) main.o graph.o tsp.o -o graph


main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.o:graph.c  graph.h
	$(CC) $(FLAGS) -c graph.c

tsp2.o: tsp.c graph.h
	$(CC) $(FLAGS) -c tsp.c


.PHONY: clean all

clean:
	rm -f *.o graph
