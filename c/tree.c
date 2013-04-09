#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
  int i;
  struct tree *left;
  struct tree *right;
} Tree;

Tree * add_tree(Tree *t, int i){
  
  if(t==NULL){
    // the tree is e
    Tree *newt = malloc(sizeof(Tree));
    newt->left = NULL;
    newt->right= NULL;
    newt->i = i;
    return newt; 
  }else {
    if(t->i > i){
      t->left = add_tree(t->left, i);
    } else {
      t->right = add_tree(t->right, i);
    }
    return t;
  }
  
}

void prefix(Tree *t){
  if(t!=NULL){
    prefix(t->left);
    printf("%d ", t->i);
    prefix(t->right);
  }
}

int main(int argc, char * argv[]){
  

  Tree *t = NULL;
  t = add_tree(t,10);
  t = add_tree(t,7);
  t = add_tree(t,15);
  t = add_tree(t,11);
  t = add_tree(t,6);
  t = add_tree(t,4);
  t = add_tree(t,2);
  t = add_tree(t,16);
  
  prefix(t);
  printf("\n");
  return 0;
}