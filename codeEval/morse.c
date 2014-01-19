#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * MORSE is a tree (or a heap).
 * Construct by hand.
 */
char MORSE[64] = " ETIANMSURWDKGOHVF-L-PJBXCYZQ--54-3---2-------16-------7---8-90";

void decode(char * line) {
  unsigned int index = 0;
  unsigned int len = (unsigned)strlen(line);
  unsigned int i;
  for (i = 0; i < len; i++) {
    char c = line[i];
    if (c == ' ' || c == '\n') {
      printf("%c", MORSE[index]);
      index = 0;
    } else if (c == '.') {
      index = index*2 + 1; // go right in the heap.
    } else if (c == '-') {
      index = index*2 + 2; // go left in the heap.
    }
  }
  printf("\n");
};

int main(int argc, char * argv[]) {
  char * filename = argv[1];
  char * line = NULL;
  size_t len = 1024;

  FILE * oFile = fopen(filename, "r");
  if (oFile != NULL) {
    while ((getline(&line, &len, oFile)) != -1) {
      if (line[0] != '\n') {
        decode(line);
        //printf("%s", line);
      }
    }
  }
  return 0;
};


/**
A	. _
B	_ . . .t
C	_ . _ .t
D	_ . .t
E	.t
F	. . _ .t
G	_ _ .t
H	. . . .t
I	. .t
J	. _ _ _
K	_ . _
L	. _ . .t
M	_ _
N	_ .t
O	_ _ _
P	. _ _ .t
Q	_ _ . _
R	. _ .t
S	. . .t
T	_
U	. . _
V	. . . _
W	. _ _
X	_ . . _
Y	_ . _ _
Z	_ _ . .t

0	_ _ _ _ _
1	. _ _ _ _
2	. . _ _ _
3	. . . _ _
4	. . . . _
5	. . . . .t
6	_ . . . .t
7	_ _ . . .t
8	_ _ _ . .t
9	_ _ _ _ .t
*/
