#include "KDTree.h"
#include <algorithm>
#include <iostream>
#include "Vertex.h"
#include <boost/unordered_set.hpp>

#define MAX_DEPTH 5

using namespace std;

/************
 * KDTreeNode
 */
KDTreeNode::KDTreeNode(){}

KDTreeNode::KDTreeNode(BoundingBox oBoundingBox, int depth):
    _oBoundingBox(oBoundingBox), _iDepth(depth) {

}

KDTreeNode::KDTreeNode(BoundingBox oBoundingBox,
                       const vector<const Triangle*> & triangles,
                       int depth):
    _oBoundingBox(oBoundingBox), _iDepth(depth), _vTriangles(triangles) {

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

/*************
 * KDTreeLeaf
 */
/**
 * @brief KDTreeLeaf::KDTreeLeaf
 * @param oBoundingBox
 * @param triangles
 * @param iDepth
 */
KDTreeLeaf::KDTreeLeaf(BoundingBox oBoundingBox,
           const std::vector<const Triangle*> & triangles, int iDepth) :
            KDTreeNode(oBoundingBox, triangles, iDepth) {

}

/************
 * KDTree
 */
KDTree::KDTree() {}
KDTree::KDTree(const vector<Vertex> & vertices,
               const vector<Triangle> & triangles,
               int depth) {

}

KDTreeNode * KDTree::getRoot() {
    return _poRoot;
}

int KDTree::getCurrentAxis() {
    return _iCurrentAxis;
}

BoundingBox KDTree::createBoundingBox(const vector<Vertex> & vertices) {
    if (vertices.empty()) {
        throw "Try to create an empty BoundingBox ";
    }
    vector<Vertex>::const_iterator it = vertices.begin();
    Vec3Df minVec3D, maxVec3D;
    minVec3D = (*it).getPos();
    maxVec3D = (*it).getPos();
    for (it; it != vertices.end(); ++it) {
        minVec3D[0] = min(minVec3D[0], (*it).getPos()[0]);
        minVec3D[1] = min(minVec3D[1], (*it).getPos()[1]);
        minVec3D[2] = min(minVec3D[2], (*it).getPos()[2]);
        maxVec3D[0] = max(maxVec3D[0], (*it).getPos()[0]);
        maxVec3D[1] = max(maxVec3D[1], (*it).getPos()[1]);
        maxVec3D[2] = max(maxVec3D[2], (*it).getPos()[2]);
    }

    return BoundingBox(minVec3D, maxVec3D);
}

BoundingBox KDTree::createBoundingBox(const boost::unordered_set<Vertex*> & vertices) {
    if (vertices.empty()) {
        throw "Try to create an empty BoundingBox ";
    }
    boost::unordered_set<Vertex*>::const_iterator it = vertices.begin();
    Vec3Df minVec3D, maxVec3D;
    minVec3D = (**it).getPos();
    maxVec3D = (**it).getPos();
    for (it; it != vertices.end(); ++it) {
        minVec3D[0] = min(minVec3D[0], (**it).getPos()[0]);
        minVec3D[1] = min(minVec3D[1], (**it).getPos()[1]);
        minVec3D[2] = min(minVec3D[2], (**it).getPos()[2]);
        maxVec3D[0] = max(maxVec3D[0], (**it).getPos()[0]);
        maxVec3D[1] = max(maxVec3D[1], (**it).getPos()[1]);
        maxVec3D[2] = max(maxVec3D[2], (**it).getPos()[2]);
    }

    return BoundingBox(minVec3D, maxVec3D);
}
