CC = gcc
FLAGS = -std=c11 -Wall -Wextra

test: main.o
	$(CC) build/main.o -o build/test

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o build/main.o

clean:
	rm -f build/*
	@echo "Cleaning done!"
