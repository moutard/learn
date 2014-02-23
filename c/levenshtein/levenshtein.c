#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int optimizeLevenshteinDistance(char * s, char * t) {

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
    unsigned int iCurrentMin = iSLength + iTLength;
    for (unsigned int k = 0; k < iTLength + 1; ++k) {
      v0[k] = v1[k];
      if (v0[k] < iCurrentMin) {iCurrentMin = v0[k];}
    }
    // If on the line the current min is more than 2 then the distance can only
    // increase. So it allows to stop before the end of the word.
    // it's just a samll trick it doesn't decrease complexity.
    if (iCurrentMin > 1) return 2;
  }
  return v1[iTLength];
};

int main(int argc, char *argv[]) {
  unsigned int MAX_INPUTS = 30;
  FILE * oFile = fopen(argv[1], "r");
  char * sEndOfInput = "END OF INPUT\n";
  char line[256];
  char * inputs[30];
  unsigned int inputsNumber[30];

  for (unsigned int i = 0; i < MAX_INPUTS; ++i) {
    inputsNumber[i] = 0;
  }
  unsigned int numberOfInputs = 0;

  while(fgets(line, 256, oFile) != NULL && strcmp(line, sEndOfInput) != 0) {
    // Store the input.
    inputs[numberOfInputs] = malloc(strlen(line) + 1);
    strcpy(inputs[numberOfInputs], line);
    // printf("%s", line);
    ++numberOfInputs;
  }

  while(fgets(line, 256, oFile) != NULL) {
    // For each words compute the levenshtein ditance for each input.
    for (unsigned int k = 0; k < numberOfInputs; ++k) {
      if (optimizeLevenshteinDistance(inputs[k], line) <= 1) {
        inputsNumber[k]++;
      }
    }
  }

  for (unsigned int i = 0; i < numberOfInputs; i++) {
    printf("%d\n", inputsNumber[i]);
  }
  for (unsigned int j = 0; j < numberOfInputs; j++) {
    free(inputs[j]);
  }

  fclose(oFile);
  return 0;
}
