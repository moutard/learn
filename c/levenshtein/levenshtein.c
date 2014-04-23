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

/**
 * 2 strings are friends if and only if their levenshtein ditance is 1.
 */
unsigned int areFriends(char * s, char * t) {

  // Degenerate Cases.
  unsigned int iSLength = strlen(s);
  unsigned int iTLength = strlen(t);
  if ((iSLength == iTLength) &&  (strcmp(s,t)==0)) {
    // not valid we do not count the same word twice.
    return 0;
  }

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

    // Use the formula to fill in the rest of the row.
    for (unsigned int j = 0; j < iTLength; ++j) {
      unsigned int cost = (s[i] == t[j]) ? 0 : 1;
      v1[j+1] = min(v1[j] + 1, v0[j+1] + 1, v0[j] + cost);
    }

    // copy v1 (current row) to v0;
    unsigned int iStillValid = 0;
    for (unsigned int k = 0; k < iTLength + 1; ++k) {
      v0[k] = v1[k];
      iStillValid = iStillValid || (v1[k] == 1);
    }
    // If on the line the current min is more than 2 then the distance can only
    // increase. So it allows to stop before the end of the word.
    // it's just a samll trick it doesn't decrease complexity.
    if (iStillValid == 0) return 0;
  }
  return v1[iTLength];
};

int isIn(char * word, char ** list, unsigned int listLength) {
  for (unsigned int i = 0; i < listLength; i++) {
    if (strcmp(word, list[i]) == 0) {
      return 1;
    }
  }
  return 0;
};

int main(int argc, char *argv[]) {
  // According to the exercise description.
  unsigned int MAX_INPUTS = 30;
  unsigned int MAX_WORDS_LIST = 10000;
  char * sEndOfInput = "END OF INPUT\n";

  // The first argument is the path of the file that contains the inputs list and
  // the dictionary.
  FILE * oFile = fopen(argv[1], "r");
  char line[64];

  // All the words (you want to compute their social network)
  char * inputs[MAX_INPUTS];
  // The max size of the social network is the list itself in the worst case.
  char ** socialNetwork = malloc(sizeof(char *) * MAX_WORDS_LIST);
  // Use to store the max number of differences (32 max ou 64)
  unsigned int inputsSNLength[MAX_INPUTS];

  for (unsigned int i = 0; i < MAX_INPUTS; ++i) {
    inputsSNLength[i] = 0;
  }

  unsigned int numberOfInputs = 0;
  while(fgets(line, 64, oFile) != NULL && strcmp(line, sEndOfInput) != 0) {
    // Store the input.
    inputs[numberOfInputs] = malloc(strlen(line) + 1);
    strcpy(inputs[numberOfInputs], line);
    ++numberOfInputs;
  }
  long iBegin = ftell(oFile);


  for (unsigned int k = 0; k < numberOfInputs; ++k) {
    socialNetwork[0] = malloc(strlen(inputs[k]) + 1);
    strcpy(socialNetwork[0], inputs[k]);

    unsigned int iSNLength = 1;
    unsigned int iSNLevel = 0;
    while(iSNLevel < iSNLength) {
      unsigned int iSNPrevious = iSNLength;
      fseek(oFile, iBegin, SEEK_SET);
      while(fgets(line, 64, oFile) != NULL) {
        // For each words compute the levenshtein ditance for each input.
        unsigned int ld = areFriends(socialNetwork[iSNLevel], line);
        if (ld == 1 && !isIn(line, socialNetwork, iSNLength)) {
          socialNetwork[iSNLength] = malloc(strlen(line) + 1);
          strcpy(socialNetwork[iSNLength], line);
          ++iSNLength;
        }
      }
      ++iSNLevel;
    }

    printf("%i\n", iSNLength);

    for (unsigned int i = 0; i < iSNLength; ++i) {
      free(socialNetwork[i]);
    }
  }

  fclose(oFile);
  // Free memory.
  for (unsigned int i = 0; i < numberOfInputs; ++i) {
    free(inputs[i]);
  }
  free(socialNetwork);

  return 0;
}
