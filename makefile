CC = gcc
FLAGS = -std=c11 -Wall -Wextra

example: main.o string_arena.o
	$(CC) build/main.o build/string_arena.o -o build/example

main.o: main.c string_arena.h
	$(CC) $(FLAGS) -c main.c -o build/main.o

string_arena.o: string_arena.c string_arena.h
	$(CC) $(FLAGS) -c string_arena.c -o build/string_arena.o

clean:
	rm -f build/*
	@echo "Cleaning done!"

run:
	@echo "Building.."
	make
	@echo "executing..."
	./build/example
