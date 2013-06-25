#include "stdlib.h"
#include <stdio.h>

unsigned int numberOfOnes(unsigned int input) {
  unsigned int result = 0;
  while(input) {
    result += (input & 1);
    input = input >> 1;
    //printf("%d\n", input);
  }
  return result;
};

int main(int argc, char * argv[]) {
  printf("%d\n", numberOfOnes(10));
  printf("%d\n", numberOfOnes(22));
  printf("%d\n", numberOfOnes(56));
}
