CC = gcc
FLAGS = -Wall -g

all:frequency

frequency: frequency.o
	$(CC) $(FLAGS) -o frequency frequency.o

frequency.o: frequency.c trie.h
	$(CC) $(FLAGS) -c frequency.c 

.PHONY: clean all

clean:
	rm *.o frequency

