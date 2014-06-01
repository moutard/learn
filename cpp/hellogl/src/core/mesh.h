#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include "vertex.h"
#include "triangle.h"
#include "edge.h"
#include "../utils/hgexception.h"

class Mesh {
public:
    inline Mesh () {}
    inline Mesh (const std::vector<Vertex> & v)
        : vertices (v) {}
    inline Mesh (const std::vector<Vertex> & v,
                 const std::vector<Triangle> & t)
        : vertices (v), triangles (t)  {}
    inline Mesh (const Mesh & mesh)
        : vertices (mesh.vertices),
          triangles (mesh.triangles) {}

    void reserve (unsigned int nbVertices, unsigned int nbTriangles);


    inline virtual ~Mesh () {}
    std::vector<Vertex> & getVertices () { return vertices; }
    const std::vector<Vertex> & getVertices () const { return vertices; }
    std::vector<Triangle> & getTriangles () { return triangles; }
    const std::vector<Triangle> & getTriangles () const { return triangles; }
    void pushVertex (Vertex vertex);
    void pushTriangle (Triangle triangle);

    void clear ();
    void clearGeometry ();
    void clearTopology ();
    void unmarkAllVertices ();
    void recomputeSmoothVertexNormals (unsigned int weight);
    void computeTriangleNormals (std::vector<Vec3Df> & triangleNormals);
    void collectOneRing (std::vector<std::vector<unsigned int> > & oneRing) const;
    void collectOrderedOneRing (std::vector<std::vector<unsigned int> > & oneRing) const;
    void computeDualEdgeMap (EdgeMapIndex & dualVMap1, EdgeMapIndex & dualVMap2);
    void markBorderEdges (EdgeMapIndex & edgeMap);

    void renderGL (bool flat) const;
    void draw () const;
    void loadOFF (const std::string & filename);

private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
};

#endif // MESH_H
