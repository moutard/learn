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
  if ((iSLength == iTLength) &&  s == t) {
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
  char * sEndOfInput = "END OF INPUT\n";

  unsigned int MAX_INPUTS = 30;
  char * inputs[MAX_INPUTS];

  unsigned int MAX_SOCIAL = 5000;
  char ** socialNetwork = malloc(sizeof(char *) * MAX_SOCIAL);

  unsigned int MAX_DICT = 300000;
  char** dict = malloc(MAX_DICT * sizeof(char*));

  for (unsigned int i = 0; i < MAX_DICT; ++i) {
    dict[i] = NULL;
  }


  unsigned int iInputId = 0;

  // Read file and fill arrays.
  FILE * oFile = fopen(argv[1], "r");
  char line[64];
  // Read inputs
  unsigned int numberOfInputs = 0;
  while(fgets(line, 64, oFile) != NULL && strcmp(line, sEndOfInput) != 0) {
    printf("%s", line);
    // Store the input.
    inputs[numberOfInputs] = malloc(strlen(line) + 1);
    strcpy(inputs[numberOfInputs], line);
    ++numberOfInputs;
  }
  // Read words of dict
  unsigned int numberOfWords = 0;
  while(fgets(line, 64, oFile) != NULL) {
    dict[numberOfWords] = malloc(strlen(line) + 1);
    strcpy(dict[numberOfWords], line);
    ++numberOfWords;
  }
  fclose(oFile);

  socialNetwork[0] = inputs[iInputId];

  unsigned int iSNLength = 1;
  unsigned int iSNLevel = 0;
  while(iSNLevel < iSNLength) {
    unsigned int iSNPrevious = iSNLength;
    for (unsigned int iWord = 0; iWord < numberOfWords; ++iWord) {
      // For each words compute the levenshtein ditance for each input.
      unsigned int ld = areFriends(socialNetwork[iSNLevel], dict[iWord]);
      if (ld == 1 && !isIn(dict[iWord], socialNetwork, iSNLength)) {
        socialNetwork[iSNLength] = dict[iWord];
        ++iSNLength;
      }
    }
    for (unsigned int i = iSNPrevious; i < iSNLength; ++i) {
      printf("%s ", socialNetwork[i]);
    }
    printf("------ %s -------- (%i / %i) \n",
        socialNetwork[iSNLevel], iSNLevel, iSNLength);
    ++iSNLevel;
  }

  printf("\n");

  for (unsigned int i = 0; i < numberOfWords; ++i) {
    free(dict[i]);
  }
  free(dict);
  // Free memory.
  for (unsigned int i = 0; i < numberOfInputs; ++i) {
    free(inputs[i]);
  }
  free(socialNetwork);

  return 0;
}
