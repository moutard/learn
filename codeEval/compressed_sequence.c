#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress(char * line) {
  unsigned int current_count = 0;
  char * current_value = NULL;
  char * value;
  value = current_value = strsep(&line, " ");
  value = current_value = strsep(&value, "\n");
  current_count = 1;
  // if there is no space strsep returns the entire string.
  while (value = strsep(&line, " ")) {
    value = strsep(&value, "\n");
    if (strcmp(current_value, value) == 0) {
      current_count++;
    } else {
      printf("%d %s ", current_count, current_value);
      current_value = value;
      current_count = 1;
    }
  }
  printf("%d %s\n", current_count, current_value);
};

int main(int argc, char * argv[]) {
  char * filename = argv[1];
  char * line = NULL;
  size_t len = 1024;

  FILE * oFile = fopen(filename, "r");
  if (oFile != NULL) {
    while ((getline(&line, &len, oFile)) != -1) {
      if (line[0] != '\n') {
        compress(line);
      }
    }
  }
  return 0;
};

