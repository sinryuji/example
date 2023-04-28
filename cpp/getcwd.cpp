#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char * curr_dir = getcwd(NULL, 0);

  if ( curr_dir == NULL ) {
    fprintf(stderr, "Error: getcwd() cannot execute\n") ;
    exit(1);
  }
  printf("Current Directory: %s\n", curr_dir) ;
  free(curr_dir);
  return 0 ;
}
