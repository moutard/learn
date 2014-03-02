#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

int levenshteinDistance(char * s, char * t) {

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
  // According to the exercise description.
  unsigned int MAX_INPUTS = 200;
  char * sEndOfInput = "END OF INPUT\n";

  FILE * oFile = fopen(argv[1], "r");
  char line[64];

  char * inputs[MAX_INPUTS];
  // Use to store the max number of differences (32 max ou 64)
  unsigned int maxLevenshtein[MAX_INPUTS];
  unsigned int inputsNumber[MAX_INPUTS];

  for (unsigned int i = 0; i < MAX_INPUTS; ++i) {
    inputsNumber[i] = 0;
    maxLevenshtein[i] = 0; // 1 = 2^0 (0 -> 1 distance lev max)
  }
  unsigned int numberOfInputs = 0;

  while(fgets(line, 64, oFile) != NULL && strcmp(line, sEndOfInput) != 0) {
    // Store the input.
    inputs[numberOfInputs] = malloc(strlen(line) + 1);
    strcpy(inputs[numberOfInputs], line);
    // printf("%s", line);
    ++numberOfInputs;
  }

  while(fgets(line, 64, oFile) != NULL) {
    // For each words compute the levenshtein ditance for each input.
    for (unsigned int k = 0; k < numberOfInputs; ++k) {
      // we do not count the word.
      unsigned int ld = levenshteinDistance(inputs[k], line);
      if (ld < 5) maxLevenshtein[k]++;

    }
  }

  for (unsigned int i = 0; i < numberOfInputs; ++i) {
    printf("%s - %i\n", inputs[i], maxLevenshtein[i]);
  }

  // Free memory.
  for (unsigned int i = 0; i < numberOfInputs; ++i) {
    free(inputs[i]);
  }

  fclose(oFile);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%fs", time_spent);
  return 0;
}
