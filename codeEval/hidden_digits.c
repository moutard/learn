#include <stdio.h>
#include <string.h>

unsigned int BUFFER_SIZE = 1024;

int decode (char * buffer) {

  // Return.
  int iErrorCode = 0;

  // The last character is the null \0.
  unsigned int iLength = (unsigned)strlen(buffer);
  unsigned int i;
  for (i = 0; i <  iLength; ++i) {
    char cCurrentChar = buffer[i];
    char a = 97; // number according to asci table.
    char j = 106;
    char zero = 48;
    char neuf = 57;

    // Reach the end of the line.
    // if nothing to print in the buffer return 3.
    if (cCurrentChar == '\n') {
      if (iErrorCode) {
        return 2;
      } else {
        return 3;
      }
    }

    if (a <= cCurrentChar && cCurrentChar <= j) {
      buffer[i] -= 49;
      iErrorCode = 1;
    } else if (zero <= cCurrentChar && cCurrentChar <= neuf) {
      iErrorCode = 1;
    } else {
      buffer[i] = 46; // point by default.
    }
  }
  return iErrorCode;
};

void printDecodedBuffer(const char * c) {

  unsigned int i;
  for (i=0; i < strlen(c); i++) {
    if (c[i] != 46 && c[i] != '\n') {
      printf("%c", c[i]);
    }
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
      if (buffer[0] != '\n') {
        // the last character of the buffer is null. \0
        // so there is only iSizeBuffer -1 letters in the buffer.
        int iErrorCode = decode(buffer);
        if (iErrorCode == 1) {
          iLineCode = 1;
          printDecodedBuffer(buffer);
        } else if (iErrorCode == 2) {
          printDecodedBuffer(buffer);
          printf("\n");
          iLineCode = 0;
        } else if (iErrorCode == 3) {
          if (iLineCode == 0) printf("NONE");
          printf("\n");
          iLineCode = 0;
        }
      } else if (iLineCode != 0) {
        printf("\n");
        iLineCode = 0;
      }

    }
    fclose(oFile);
  }

};

int main(int argc, char * argv[]) {
  char * filename = argv[1];
  readFileByBuffer(filename, BUFFER_SIZE);
  return 0;
};
