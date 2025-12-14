/*
StringArena — Example
--------------------------------
A small example showing the usage of the StringArena
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "string_arena.h"

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
