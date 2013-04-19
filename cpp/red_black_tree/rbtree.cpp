#include "rbtree.h"
#include <iostream>
using namespace std;

RBTree::RBTree()
{
    root = NULL;
}

RBTree::RBTree(const vector<int> &v){
    root = NULL;
    for(unsigned int i=0; i < v.size(); i++){
        insert(root, v[i]);
    }
}

/**
 * We need to pass ht epointer as a reference because we want to modify it (and not whta it contains.)
 * See c++ quizz for more informations.
 */
void RBTree::insert(RBTreeNode * &root, int value){
    if(root == NULL){
        RBTreeNode * newElement = new RBTreeNode(value);
        root = newElement;
        //cout << newElement->getValue() << endl;
    } else if(root->getValue() < value) {
        insert(root->right, value);
    } else {
        insert(root->left, value);
    }
}


RBTree::~RBTree(){
    removeWithDepthFirst(root);
}

void RBTree::removeWithDepthFirst(RBTreeNode * &element){
  if(element != NULL){
        RBTreeNode * right = element->getRight();
        RBTreeNode * left = element->getLeft();
        removeWithDepthFirst(right);
        removeWithDepthFirst(left);
        cout << "delete " << element->getValue() << endl;
        delete element;
  }
}

void RBTree::preOrder(){
    preOrder(root);
}

void RBTree::preOrder(RBTreeNode * element){
    if(element != NULL){
        preOrder(element->getLeft());
        cout << element->getValue() << endl;
        preOrder(element->getRight());
    }
}


