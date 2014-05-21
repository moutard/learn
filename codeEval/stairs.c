#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const unsigned int MAX = 1024;
unsigned long FIB[1024];
/**
 * Problem
 * even for 64 bits.
 */
unsigned long fibonacci (unsigned int i) {
  if (i < MAX  && FIB[i] != 0) return FIB[i];
  if (i == 0) return 0;
  if (i == 1) return 1;
  if (i == 2) return 1;
  if (i == 3) return 2;
  FIB[i] = fibonacci(i-1) + fibonacci(i-2);
  return FIB[i];
}

/**
 * You have two possible cases: either the path goes through the n-1th step or it
 * doesn't. If it goes through it, then there are f(n-1) ways to get to the n-1th
 * step and just one way to finish in all these paths. If the path does not go
 * through the n-1th step, then it must go through the n-2th step. In this case
 * there are f(n-2) ways to reach this step and one way to finish in each case
 * (by jumping 2 steps). Both approaches lead to the recursion relation
 * f(n) = f(n-1) + f(n-2).
 */
int main(int argc, char *argv[]) {
  // According to the exercise description.



  for (unsigned int i = 0; i < MAX; ++i) {
    FIB[i] = 0;
  }
  FILE * oFile = fopen(argv[1], "r");
  char line[8];

  while(fgets(line, 8, oFile) != NULL) {
    printf("%lu\n", fibonacci(atoi(line)+1));
  }

  fclose(oFile);
}

