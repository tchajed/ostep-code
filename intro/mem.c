#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int *p = malloc(sizeof(int) * 10 /* GB */ * 1024 * 1024 * 1024);
  assert(p != NULL);
  printf("(%d) addr pointed to by p: %p\n", getpid(), p);
  *p = 0;
  while (1) {
    Spin(1);
    *p = *p + 1;
    printf("(%d) value of p: %d\n", getpid(), *p);
  }
  return 0;
}
