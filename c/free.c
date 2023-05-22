#include <stdio.h>
#include <stdlib.h>

int main() {
  char* str;

  printf("%p\n", str);
  str = malloc(sizeof(char) * 10);
  printf("%p\n", str);
  free(str);
  printf("%p\n", str);
}
