#ifndef KDTREE_H
#define KDTREE_H

#include <vector>


#include "Vertex.h"
#include "Triangle.h"
#include "BoundingBox.h"

/**
 * @brief The KDTreeNode class
 * Node of tree, we use the boundingbox to know where to find the next
 * triangles.
 * All triangles that are in both left and right trees are stored directly in the
 * node to decrease the BoundingBox, and avoid duplication.
 */
class KDTreeNode {
public:
    KDTreeNode();
    KDTreeNode(BoundingBox oBoundingBox, int depth);
    ~KDTreeNode();
    std::vector<const Triangle*> & getTriangles();
    BoundingBox & getBoundingBox();
    int getDepth();
    bool isLeaf();
protected:
    // False if node True if leaf.
    bool _bIsLeaf;
    // The boundingBox is used to know when whe have to go left, right or both.
    BoundingBox _oBoundingBox;
    // vector of triangles' id.
    // Common triangles in both subtrees are stored directly in the node.
    std::vector<const Triangle*> _vTriangles ;
    // Depth of the node is the tree
    int _iDepth;
    // Axis used to cut the 3D space.
    int _iAxis;
    KDTreeNode * _poLeft;
    KDTreeNode * _poRight;
};

/**
 * @brief The KDTreeLeaf class
 * Leaf store the final Triangles
 */
class KDTreeLeaf : public KDTreeNode {
    KDTreeLeaf(BoundingBox oBoundingBox,
               const std::vector<const Triangle*> & triangles, int iDepth);
    ~KDTreeLeaf(){};
};

/**
 * @brief The KDTree class
 * Englobe KDTreeNode
 */
class KDTree {

public:
    KDTree();
    KDTree(const std::vector<Vertex> & vertices, const std::vector<Triangle> & triangles, int depth);
    KDTreeNode * getRoot();
    int getCurrentAxis();
    BoundingBox getBoundingBox(const std::vector<Vertex> & vertices);

    struct sortstruct {
      // sortstruct needs to know its containing object
      KDTree * _tree;
      sortstruct(KDTree * tree) : _tree(tree) {};

      // this is our sort function, which makes use
      // of some non-static data (sortascending)
      bool operator() (int vertex_id_1, int vertex_id_2) {
        return _tree->_vertices[vertex_id_1].getPos()[_tree->getCurrentAxis()]
          < _tree->_vertices[vertex_id_2].getPos()[_tree->getCurrentAxis()];
      }
    };
private:
    KDTreeNode * _poRoot;
    std::vector<Vertex> _vertices;
    std::vector<Triangle> _triangles;
    int _iCurrentAxis;
};

#endif // KDTREE_H
