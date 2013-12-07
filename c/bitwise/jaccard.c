#include <stdlib.h>
#include <stdio.h>

inline int count_number_bits_set(long l) {
 unsigned int c;
  for(c=0;l;c++)
   l &= l-1;
 return c;
}

int main(int argc, char** argv){
  int c = count_number_bits_set(389349);
  printf("%i", c);
  return 0;
}
