#include <stdlib.h> // needed for malloc declaration.

// Define a type for this struct, to avoid to long notation
// struct node * n = NULL;
// instead
// Node * n = NULL;
typedef struct {
  int value;
  struct LinkedList * next;
} LinkedList;


int main(){
  // A malloc so you need a free.
  LinkedList *n = malloc(sizeof(LinkedList));

  free(n);
  return 0;
};
