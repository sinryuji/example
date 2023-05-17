#include <stdio.h>

int main(void) {
  char buf[100];
  sprintf(buf, "%s", "hi");
  printf("%s", buf);
}
