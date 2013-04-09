#include <stdlib.h> // needed for malloc declaration.
#include <stdio.h>  // needed for printf

// Define a type for this struct, to avoid to long notation
// struct linked_list * n = NULL;
// instead
// LinkedList * n = NULL;
typedef struct linked_list {
  int value;
  struct linked_list * next;
} LinkedList;

LinkedList * add_value(LinkedList *l, int value){
  LinkedList *newElement = malloc(sizeof(LinkedList));
  newElement->value = value;
  newElement->next = l;
  return newElement;
};

void print_linked_list(LinkedList *l){
  LinkedList * p = l;
  while(p!=NULL){
    printf("%d", p->value);
    p = p->next;
  }
};

void free_linked_list(LinkedList *l){
  LinkedList * currentNode = l;
  LinkedList * temp = NULL;
  while(currentNode!=NULL){
    temp = currentNode;
    currentNode = currentNode->next;
    free(temp);
  }
  l = NULL;
};

int main(){
  // A malloc so you need a free.
  LinkedList *n = NULL;
  n = add_value(n, 5);
  n = add_value(n, 6);
  n = add_value(n, 7);

  print_linked_list(n);
  free_linked_list(n);
  return 0;
};
