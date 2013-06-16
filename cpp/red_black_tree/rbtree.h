#ifndef RBTREE_H
#define RBTREE_H
#include <stdlib.h>
#include <vector>
using namespace std;
class RBTreeNode {

public:
    RBTreeNode();
    RBTreeNode(int _value){
        value = _value;
        left = NULL;
        right = NULL;
    };

    int getValue(){return value;}
    void setColor(int _color){
        color = _color;
    }
    void setValue(int _value){
        value = _value;
    }
    RBTreeNode * getLeft(){return left;}
    RBTreeNode * getRight(){return right;}
    int value;
    int color;

    RBTreeNode * left;
    RBTreeNode *right;


};

class RBTree
{
public:
    RBTree();
    RBTree(const vector<int> & v);
    ~RBTree();
    void insert(RBTreeNode * &node, int value);
    void preOrder();
    void inOrder();
    void removeWithDepthFirst(RBTreeNode * &element);
    void rotateLeft(RBTreeNode * &element);
    void rotateRight(RBTreeNode * &element);
    void rotateRight();
private:
    RBTreeNode * root;
    void preOrder(RBTreeNode * element);
    void inOrder(RBTreeNode * element);
};


#endif // RBTREE_H
