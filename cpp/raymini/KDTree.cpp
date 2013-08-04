#include "KDTree.h"
#include <algorithm>
#include "Vertex.h"
#define MAX_DEPTH 5

KDTreeNode::KDTreeNode(){}

KDTreeNode::KDTreeNode(BoundingBox oBoundingBox, int depth):
    _oBoundingBox(oBoundingBox), _iDepth(depth) {

}

KDTreeNode::~KDTreeNode() {

}

std::vector<const Triangle*> & KDTreeNode::getTriangles() {
    return _vTriangles;
}

BoundingBox & KDTreeNode::getBoundingBox() {
    return _oBoundingBox;
}

int KDTreeNode::getDepth() {
    return _iDepth;
}

bool KDTreeNode::isLeaf() {
    return _bIsLeaf;
}

KDTreeNode * KDTreeNode::getLeft() {
    return _poLeft;
}

KDTreeNode * KDTreeNode::getRight() {
    return _poRight;
}
