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

RBTree::~RBTree(){
    depthFirst(root);
}

void RBTree::depthFirst(RBTreeNode * element){
    cout << element->getValue() << endl;
    if(element->getLeft()==NULL && element->getRight()==NULL){
        delete element;
        element = NULL;
    } else if(element->getLeft()==NULL){
        depthFirst(element->getRight());
    } else {
        depthFirst(element->getLeft());
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

void RBTree::insert(RBTreeNode * root, int value){
    if(root == NULL){
        RBTreeNode * newElement = new RBTreeNode(value);
        root = newElement;
        cout << newElement->getValue() << endl;
    } else if(root->getValue() < value) {
        insert(root->getRight(), value);
    } else {
        insert(root->getLeft(), value);
    }
}
