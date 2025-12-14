/*
StringArena — Design & Invariants
--------------------------------

StringArena is a minimal string arena allocator that stores multiple
null-terminated strings in a single contiguous memory buffer.

Core invariants:

1. `data` points to a contiguous memory region of size `size` bytes.
2. Strings are stored back-to-back and are always null-terminated (`'\0'`).
3. `offsets[i]` stores the starting byte offset of the i-th string in `data`.
4. `count` is the number of strings currently stored.
5. `capacity` is the allocated capacity of the `offsets` array (not bytes).
6. Offsets are monotonically increasing.
7. `arena_getS()` returns a pointer to a valid C string as long as the arena
   is not resized or freed.

Memory model:

- Individual strings are NOT allocated separately.
- All string data lives in a single growable buffer.
- Returned string pointers remain valid until:
  - `arena_addS()` reallocates the buffer
  - `arena_free()` is called
  - `arena_reset()` is called

This design favors:
- Cache locality
- Fewer allocations
- Simple lifetime management

This is a minimal implementation, not thread-safe.
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringArena {
  char *data;
  size_t size;

  size_t *offsets;
  size_t count;
  size_t capacity;

} StringArena;

StringArena arena_create() { return (StringArena){0}; }

void arena_addS(struct StringArena *arena, char *val) {
  size_t len = strlen(val) + 1;

  if (arena->count == arena->capacity ||
      (arena->count + len) >= arena->capacity) {

    size_t new_cap = arena->capacity == 0 ? 4 : arena->capacity * 2;
    void *tmp = realloc(arena->offsets, new_cap * sizeof(size_t));

    if (!tmp) {
      return;
    }
    arena->offsets = tmp;
    arena->capacity = new_cap;
  }

  char *buf = realloc(arena->data, arena->size + len);

  if (!buf)
    return;

  arena->data = buf;

  arena->offsets[arena->count] = arena->size;
  memcpy(arena->data + arena->size, val, len);

  arena->size += len;
  arena->count++;
}

const char *arena_getS(StringArena *arena, size_t i) {
  if (i >= arena->count) {
    return NULL;
  }

  return arena->data + arena->offsets[i];
}

void arena_free(StringArena *arena) {
  free(arena->data);
  free(arena->offsets);
}

void arena_reset(StringArena *arena) {
  arena->capacity = 0;
  arena->count = 0;
}

int main() {
  printf("Hello, World! \n");
  StringArena v = arena_create();

  arena_addS(&v, "Foo \n");
  arena_addS(&v, "Bar \n");

  arena_addS(&v, "PO PO PO PO\n");
  const char *slice = arena_getS(&v, 0);
  printf("slice contents: %s", slice);

  arena_free(&v);
  return 0;
}
