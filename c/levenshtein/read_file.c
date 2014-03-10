#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int lev(char * s1, char * s2) {
  return 0;
};

unsigned int min(unsigned int a, unsigned int b, unsigned int c) {
  unsigned int min;
  if (a < b) {
    min = a;
  } else {
    min = b;
  }

  if (c < min) {
    return c;
  } else {
    return min;
  }
};

int levenshtein(char * s, char * t) {

  // Degenerate Cases.
  if (strcmp(s,t)==0) { return 0;}
  unsigned int iSLength = strlen(s);
  unsigned int iTLength = strlen(t);
  if (iSLength == 0) {return iTLength;}
  if (iTLength == 0) {return iSLength;}

  // Create the two vectors (corresponds to the previous and current line of the matrix)
  unsigned int v0[iTLength + 1];
  unsigned int v1[iTLength + 1];

  // Initialize each vector.
  for (unsigned int i = 0; i < iTLength + 1; ++i) {
    v0[i] = i;
  }

  for (unsigned int i = 0; i < iSLength; ++i) {
    // Calculate v1 (the current row distance)
    v1[0] = i + 1;

    // Use the formulat to fill in the rest of the row.
    for (unsigned int j = 0; j < iTLength; ++j) {
      unsigned int cost = (s[i] == t[j]) ? 0 : 1;
      v1[j+1] = min(v1[j] + 1, v0[j+1] + 1, v0[j] + cost);
    }

    // copy v1 (current row) to v0;
    for (unsigned int k = 0; k < iTLength + 1; ++k) {
      v0[k] = v1[k];
    }
  }
  return v1[iTLength];
};

int main(int argc, char *argv[]) {
  clock_t begin, end;
  double time_spent;
  begin = clock();

  FILE * oFile = fopen(argv[1], "r");
  char line[64];
  long iCursor = 0;
  char sTestWord[9] = "bonjour\n";

  while (iCursor < 30) {
    rewind(oFile);
    while(fgets(line, 64, oFile) != NULL) {
      levenshtein(line, sTestWord);
    }
    ++iCursor;
  }

  fclose(oFile);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%fs\n", time_spent);
  return 0;
}
