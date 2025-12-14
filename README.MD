# String Arena

- A small C project for managing a string arena, allowing you to store 
multiple strings in a single contiguous memory block and access them efficiently.

## Features

- Dynamic storage of strings in contiguous memory.
- Retrieve individual strings by index.
- Automatic resizing as new strings are added.
- Memory cleanup when the arena is no longer needed.

## Example

```c
StringArena arena = arena_create();

arena_addS(&arena, "Hello");
arena_addS(&arena, "World");

const char *first = arena_getS(&arena, 0); // "Hello"
const char *second = arena_getS(&arena, 1); // "World"

arena_free(&arena); // Free memory
```

## Compilation

```bash
make
./build/test
```
