# String Arena

A minimal string arena allocator implemented in C.

`StringArena` stores multiple null-terminated strings in a single contiguous
memory buffer, allowing fast indexed access without individual heap allocations
per string.

This library is designed for simplicity, cache locality, and predictable
memory behavior.

## Features

- Dynamic storage of null-terminated strings in contiguous memory.
- Retrieve individual strings by index.
- Automatic resizing as new strings are added.
- Memory cleanup when the arena is no longer needed.
- Returned string pointers remain valid until:
    - the arena reallocates
    - `arena_reset()` is called
    - `arena_free()` is called

## API

```c
StringArena arena_create(void);
void arena_addS(StringArena *arena, const char *val);
const char *arena_getS(StringArena *arena, size_t index);
void arena_reset(StringArena *arena);
void arena_free(StringArena *arena);
```

## Example

```c
StringArena arena = arena_create();

arena_addS(&arena, "Hello");
arena_addS(&arena, "World");

const char *first = arena_getS(&arena, 0); // "Hello"
const char *second = arena_getS(&arena, 1); // "World"

arena_free(&arena); // Free memory
```
## Thread Safety

This Arena is **not thread-safe by design**.

Synchronization is intentionally left to the caller, allowing the arena to be
used in single-threaded, externally synchronized, or thread-local contexts
without imposing any specific concurrency model.

## Note

 - Returned string pointers may be invalidated after reallocation
 - `arena_reset()` does not free memory — it resets logical state

## Compilation

```bash
make run
```
