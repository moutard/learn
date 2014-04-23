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

unsigned int search(char * segment, char * dna, int max_distance) {
  unsigned int counter = 0;
  unsigned int segmentLength = strlen(segment);
  unsigned int dnaLength = strlen(dna);
  char substring[segmentLength + 1];
  for (unsigned int i = 0; i < (dnaLength - segmentLength + 1); ++i) {
    memcpy(substring, &dna[i], segmentLength );
    substring[segmentLength] = '\0';
    if (levenshteinDistance(segment, substring) <= max_distance) {
      counter++;
      printf("%s ", substring);
    }
  }
  printf("\n");

  return counter;
}

int main(int argc, char *argv[]) {
  // According to the exercise description.
  unsigned int MAX_INPUTS = 30;
  char * sEndOfInput = "END OF INPUT\n";

  FILE * oFile = fopen(argv[1], "r");
  char line[512]; // in fact < 300 + 40 + 50 + 2 (spaces)

  char segment[50];
  char dna[300];
  char max_distance[2];
  char * tmp;
  while(fgets(line, 512, oFile) != NULL) {
    tmp = strtok(line, " ");
    strcpy(segment, tmp);
    tmp = strtok(NULL, " ");
    strcpy(max_distance, tmp);
    tmp = strtok(NULL, " ");
    strcpy(dna, tmp);
    printf("%s\n", dna);

    printf("%u\n", search(segment, dna, atoi(max_distance)));
    // For each words compute the levenshtein ditance for each input.
    // unsigned int ld = levenshteinDistance(socialNetwork[iSNLevel], line);
  }

  fclose(oFile);
}

