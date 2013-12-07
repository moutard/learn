#include <stdlib.h>
#include <stdio.h>

void swap(char * c, int i, int j) {
  if((0 <= i) && (0 <= j)) {
    char temp = c[i];
    printf("%c\n", temp);
  }
};

int main(int argc, char * argv[]) {
  char * c = "abc";
  swap(c, 1, 0);
  return 0;
};
