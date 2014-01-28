#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
  char * filename = argv[1];
  char * line = NULL;
  size_t len = 1024;

  FILE * oFile = fopen(filename, "r");
  if (oFile != NULL) {
    while ((getline(&line, &len, oFile)) != -1) {
      if (line[0] != '\n') {
        parse(line);
      }
    }
  }
  return 0;
};

