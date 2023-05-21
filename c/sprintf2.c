#include <stdio.h>
#include <stdlib.h>

typedef struct s_struct {
  char* data;
} t_struct;

int main(void) {
  t_struct* a = malloc(sizeof(t_struct));
  a->data = NULL;
  char* msg = malloc(sizeof(char) * 1);
  char* msg2 = (char*)malloc(sizeof(char) * 4);
  msg2[0] = 'a';
  msg2[1] = 'b';
  msg2[2] = 'c';
  msg2[3] = 0;

  sprintf(a->data, "hiajsdkfwqklefjlwqfe + %s", msg2);
  printf("%s", msg);
}
