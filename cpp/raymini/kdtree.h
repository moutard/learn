#ifndef KDTREE_H
#define KDTREE_H
#include "Mesh.h"
#include <vector>
using namespace std;

class KDTreeNode {
public:
    KDTreeNode();
    KDTreeNode(vector<int> vertices);
    ~KDTreeNode();
    vector<int> getVertices();
    int getDepth();
private:
    vector<int> vertices;
    int depth;
    KDTreeNode * left;
    KDTreeNode * right;
}

class KDTree {

public:
    KDTree(Mesh & mesh);
    KDTreeNode * root();
private:
    KDTreeNode * root;
};

#endif // KDTREE_H
