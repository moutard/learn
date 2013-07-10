#include "kdtree.h"
#include <algorithm>
#include "Vertex.h"
#define MAX_DEPTH 5

bool xAxisComparator(Vertex & v0, Vertex & v1){
    return v0.getPos()[0] < v1.getPos()[0];
}
bool yAxisComparator(Vertex & v0, Vertex & v1){
    return v0.getPos()[1] < v1.getPos()[1];
}
bool zAxisComparator(Vertex & v0, Vertex & v1){
    return v0.getPos()[2] < v1.getPos()[2];
}

KDTreeNode::KDTreeNode() {

}

KDTreeNode::KDTreeNode(vector<int> _vertices, int depth) {
    if(depth < MAX_DEPTH) {
        int median = _vertices.size() / 2;
        left = KDTreeNode(_vertices, depth + 1)
    } else {
        // It's a Leaf.
        vertices = _vertices; // copy operator;
    }

}

KDTreeNode::getVertices() {
    return vertices;
}

KDTreeNode::getDepth() {
    return depth;
}

KDTree::KDTree(Mesh & mesh) {
    root = NULL;

    bool (*axisComparator)() =  xAxisComparator;
    int median = mesh.getVertices().size() / 2;
    std::sort (mesh.getVertices().begin(),
               mesh.getVertices().end(),
               axisComparator);

}
