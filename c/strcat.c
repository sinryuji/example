#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char* str = "hello";
  char* str_empty;
  char* srt2;
  
  str_empty = (char*)malloc(sizeof(char) + (strlen(str) + 1));
  strcat(str_empty, str);
  
  char* str2 = (char*)malloc(sizeof(char) + 6);
  str2[0] = 'w';
  str2[1] = 'o';
  str2[2] = 'r';
  str2[3] = 'l';
  str2[4] = 'd';
  str2[5] = 0;
  char* tmp = strdup(str2);
  str2 = (char*)realloc(str2, sizeof(char) + (strlen(str2) + strlen(str) + 1));
  strcpy(str2, str);
  strcat(str2, tmp);
  printf("%s\n", str);
  printf("%s\n", tmp);
  printf("%s\n", str2);
}
