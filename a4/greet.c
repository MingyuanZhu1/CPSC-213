#include <stdio.h>
#include <stdlib.h>

void greet(char *name) {
  static long lastId = 0;
  long id = ++lastId;
  printf("Hello %s!\n", name);
  printf("  You are visitor #%d.\n", id);
}

int main() {
  greet("Kelly");
  greet("Morgan");
  return 0;
}
