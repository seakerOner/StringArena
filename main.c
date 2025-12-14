#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringArena {
  char *banana;
  size_t size;

  size_t *offsets;
  size_t count;
  size_t capacity;
} StringArena;

StringArena arena_create() { return (StringArena){0}; }

void arena_addS(struct StringArena *arena, char *val) {
  size_t len = strlen(val) + 1;

  if (arena->count == arena->capacity || (arena->count + len) >= arena->capacity) {
    size_t new_cap = arena->capacity == 0 ? 4 : arena->capacity * 2;
    void *tmp = realloc(arena->offsets, new_cap * sizeof(size_t));
    if (!tmp)
      return;
    arena->offsets = tmp;
    arena->capacity = new_cap;
  }

  char *buf = realloc(arena->banana, arena->size + len);
  if (!buf)
    return;

  arena->banana = buf;

  arena->offsets[arena->count] = arena->size;
  memcpy(arena->banana + arena->size, val, len);

  arena->size += len;
  arena->count++;
}

const char *arena_getS(StringArena *arena, size_t i) {
  if (i >= arena->count) {
    return NULL;
  }

  return arena->banana + arena->offsets[i];
}

void arena_free(StringArena *arena) {
  free(arena->banana);
  free(arena->offsets);
}

int main() {
  printf("Hello, World! \n");
  StringArena v = arena_create();

  arena_addS(&v, "BLYATTTTTTTTTTTTTT \n");
  arena_addS(&v, "BLYATTTTTTTTTTTTTT \n");

  arena_addS(&v, "PO PO PO PO\n");
  const char *slice = arena_getS(&v, 0);
  printf("slice contents: %s", slice);

  arena_free(&v);
  return 0;
}
