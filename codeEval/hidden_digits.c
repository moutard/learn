#include <stdlib.h>
#include <stdio.h>

unsigned int BUFFER_SIZE = 5;

int decode (char * buffer, unsigned int iBufferSize) {
  unsigned int i;
  int iErrorCode = 0;
  // the last character is the null \0.
  unsigned int iLength = (unsigned)strlen(buffer);
  for (i = 0; i <  iLength; ++i) {
    char c = buffer[i];
    char a = 97; // number according to asci table.
    char j = 106;
    if (a <= c && c <= j) {
      buffer[i] -= 49;
      iErrorCode = 1;
    } else if (c == 5) {
      // end of line.
      if (iErrorCode == 0) {
        iErrorCode = 3;
      } else {
        iErrorCode = 2;
      }
    } else {
      buffer[i] = 46; // point by default.
    }
  }
  return iErrorCode;
};

void readFileByLine(char * filename) {
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  FILE * oFile = fopen(filename, "r");

  if (oFile != NULL) {
    while ((read = getline(&line, &len, oFile)) != -1 ) {
      printf("%s", line);
    }
  }

};

void printDecodedBuffer(char * buffer) {
  unsigned int i;
  unsigned int iLength = (unsigned)strlen(buffer);
  for (i = 0; i <  iLength; ++i) {
    if (buffer[i] != 46) prinf("%c", buffer[i]);
  }
};

void readFileByBuffer(char * filename, unsigned int iBufferSize) {
  char buffer[iBufferSize];
  FILE * oFile = fopen(filename, "r");

  if (oFile != NULL) {
    /**
     * fread can only be used by text file written by fwrite on the same computer
     * to respect endiannes.
     */
    // size_t iNewLength = fread(buffer, sizeof(char), bufferSize, oFile);
    int iLineCode = 0;
    while (fgets(buffer, iBufferSize, oFile) != NULL) {
      // the last character of the buffer is null. \0
      // so there is only iSizeBuffer -1 letters in the buffer.
      printf("%s@", buffer);
      int iErrorCode = decode(buffer, iBufferSize);
      if (iErrorCode == 0) {
        // nothing to do.
      } else if (iErrorCode == 1) {
        iLineCode = 1;
        printDecodedBuffer(buffer);
      } else if (iErrorCode == 2) {
        printDecodedBuffer(buffer);

      } else if (iErrorCode == 3) {
        if (iLineCode == 0) printf("NONE\n");
      }
      printf("%s\n", buffer);

    }
    fclose(oFile);
  }

};

int main(int argc, char * argv[]) {
  char * filename = argv[1];
  readFileByBuffer(filename, BUFFER_SIZE);
  printf("\n");
  return 0;
};
