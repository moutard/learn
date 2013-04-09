#include <stdlib.h> // needed for malloc declaration.

// Define a type for this struct, to avoid to long notation
// struct node * n = NULL;
// instead
// Node * n = NULL;
typedef struct node {
  int i;
  struct Node * next;
} Node;

int main(){
  // A malloc so you need a free.
  Node * n = malloc(sizeof(Node));

  free(n);
  return 0;
};
