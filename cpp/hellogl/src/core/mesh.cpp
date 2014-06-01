#include "mesh.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLUT/glut.h>
#include "../utils/hgexception.h"
using namespace std;

void Mesh::clear () {
    clearTopology ();
    clearGeometry ();
}

void Mesh::clearGeometry () {
    vertices.clear ();
    cout << "clear geometry ok" << endl;
}

void Mesh::clearTopology () {
    triangles.clear ();
    cout << "clear topology ok" << endl;
}

void Mesh::unmarkAllVertices () {
    for (unsigned int i = 0; i < vertices.size (); i++)
        vertices[i].unmark ();
}

void Mesh::computeTriangleNormals (vector<Vec3Df> & triangleNormals) {
    for (vector<Triangle>::const_iterator it = triangles.begin ();
         it != triangles.end ();
         it++) {
        Vec3Df e01 (vertices[it->getVertex (1)].getPos () - vertices[it->getVertex (0)].getPos ());
        Vec3Df e02 (vertices[it->getVertex (2)].getPos () - vertices[it->getVertex (0)].getPos ());
        Vec3Df n (Vec3Df::crossProduct (e01, e02));
        n.normalize ();
        triangleNormals.push_back (n);
    }
}

void Mesh::recomputeSmoothVertexNormals (unsigned int normWeight) {
    vector<Vec3Df> triangleNormals;
    computeTriangleNormals (triangleNormals);
    for (std::vector<Vertex>::iterator it = vertices.begin (); it != vertices.end (); it++)
        it->setNormal (Vec3Df (0.0, 0.0, 0.0));
    vector<Vec3Df>::const_iterator itNormal = triangleNormals.begin ();
    vector<Triangle>::const_iterator it = triangles.begin ();
    for ( ; it != triangles.end (); it++, itNormal++)
        for (unsigned int  j = 0; j < 3; j++) {
            Vertex & vj = vertices[it->getVertex (j)];
            float w = 1.0; // uniform weights
            Vec3Df e0 = vertices[it->getVertex ((j+1)%3)].getPos () - vj.getPos ();
            Vec3Df e1 = vertices[it->getVertex ((j+2)%3)].getPos () - vj.getPos ();
            if (normWeight == 1) { // area weight
                w = Vec3Df::crossProduct (e0, e1).getLength () / 2.0;
            } else if (normWeight == 2) { // angle weight
                e0.normalize ();
                e1.normalize ();
                w = (2.0 - (Vec3Df::dotProduct (e0, e1) + 1.0)) / 2.0;
            }
            if (w <= 0.0)
                continue;
            vj.setNormal (vj.getNormal () + (*itNormal) * w);
        }
    Vertex::normalizeNormals (vertices);
}

void Mesh::collectOneRing (vector<vector<unsigned int> > & oneRing) const {
    oneRing.resize (vertices.size ());
    for (unsigned int i = 0; i < triangles.size (); i++) {
        const Triangle & ti = triangles[i];
        for (unsigned int j = 0; j < 3; j++) {
            unsigned int vj = ti.getVertex (j);
            for (unsigned int k = 1; k < 3; k++) {
                unsigned int vk = ti.getVertex ((j+k)%3);
                if (find (oneRing[vj].begin (), oneRing[vj].end (), vk) == oneRing[vj].end ())
                    oneRing[vj].push_back (vk);
            }
        }
    }
}

void Mesh::collectOrderedOneRing (vector<vector<unsigned int> > & oneRing) const {
    oneRing.resize (vertices.size ());
    for (unsigned int t = 0; t < triangles.size (); t++) {
        const Triangle & ti = triangles[t];
        for (unsigned int i = 0; i < 3; i++) {
            unsigned int vi = ti.getVertex (i);
            unsigned int vj = ti.getVertex ((i+1)%3);
            unsigned int vk = ti.getVertex ((i+2)%3);
            vector<unsigned int> & oneRingVi = oneRing[vi];
            vector<unsigned int>::iterator begin = oneRingVi.begin ();
            vector<unsigned int>::iterator end = oneRingVi.end ();
            vector<unsigned int>::iterator nj = find (begin, end, vj);
            vector<unsigned int>::iterator nk = find (begin, end, vk);
            if (nj != end && nk == end) {
                if (nj == begin)
                    nj = end;
                nj--;
                oneRingVi.insert (nj, vk);
            } else if (nj == end && nk != end)
                oneRingVi.insert (nk, vj);
            else if (nj == end && nk == end) {
                oneRingVi.push_back (vk);
                oneRingVi.push_back (vj);
            }
        }
    }
}

void Mesh::computeDualEdgeMap (EdgeMapIndex & dualVMap1, EdgeMapIndex & dualVMap2) {
    for (vector<Triangle>::iterator it = triangles.begin ();
         it != triangles.end (); it++) {
        for (unsigned int i = 0; i < 3; i++) {
            Edge eij (it->getVertex (i), it->getVertex ((i+1)%3));
            if (dualVMap1.find (eij) == dualVMap1.end ())
                dualVMap1[eij] = it->getVertex ((i+2)%3);
            else
                dualVMap2[eij] = it->getVertex ((i+2)%3);
        }
    }
}

void Mesh::markBorderEdges (EdgeMapIndex & edgeMap) {
    for (vector<Triangle>::iterator it = triangles.begin ();
         it != triangles.end (); it++) {
        for (unsigned int i = 0; i < 3; i++) {
            unsigned int j = (i+1)%3;
            Edge eij (it->getVertex (i), it->getVertex (j));
            if (edgeMap.find (eij) == edgeMap.end ())
                edgeMap[eij] = 0;
            else
                edgeMap[eij] += 1;
        }
    }
}

inline void glVertexVec3Df (const Vec3Df & v) {
    glVertex3f (v[0], v[1], v[2]);
}

inline void glNormalVec3Df (const Vec3Df & n) {
    glNormal3f (n[0], n[1], n[2]);
}

inline void glDrawPoint (const Vec3Df & pos, const Vec3Df & normal) {
    glNormalVec3Df (normal);
    glVertexVec3Df (pos);
}

inline void glDrawPoint (const Vertex & v) {
    glDrawPoint (v.getPos (), v.getNormal ());
}

void Mesh::draw () const {
    glBegin (GL_TRIANGLES);
    const Triangle & t = triangles[0];
    Vertex verticesForTheCurrentTriangles[3];
    for (unsigned int j = 0; j < 3; j++) {
        cout << j << endl;
        verticesForTheCurrentTriangles[j] = vertices[t.getVertex(j)];
    }
    for (unsigned int j = 0; j < 3; j++) {
            glNormalVec3Df (verticesForTheCurrentTriangles[j].getNormal());
            glVertexVec3Df (verticesForTheCurrentTriangles[j].getPos ());
    }
    glEnd ();
}

void Mesh::renderGL (bool flat) const {
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size (); i++) {
        const Triangle & t = triangles[i];
        Vertex v[3];
        for (unsigned int j = 0; j < 3; j++)
            v[j] = vertices[t.getVertex(j)];
        if (flat) {
            Vec3Df normal = Vec3Df::crossProduct (v[1].getPos () - v[0].getPos (),
                                                  v[2].getPos () - v[0].getPos ());
            normal.normalize ();
            glNormalVec3Df (normal);
        }
        for (unsigned int j = 0; j < 3; j++)
            if (!flat)
                glDrawPoint (v[j]);
            else
                glVertexVec3Df (v[j].getPos ());
    }
    glEnd ();
}

void Mesh::reserve(unsigned int nbVertices, unsigned int nbTriangles) {
    vertices.reserve(nbVertices);
    triangles.reserve(nbTriangles);
}

void Mesh::pushTriangle(Triangle triangle) {
    triangles.push_back(triangle);
}

void Mesh::pushVertex(Vertex vertex) {
    vertices.push_back(vertex);
}

/**
 * @brief Mesh::loadOFF
 * @param filename
 * Load a mesh file. It contains a line with the number of vertices N and the number of triangles M.
 * N lines -> vertices
 * M lines -> triangles
 */
void Mesh::loadOFF (const std::string & filename) {
    clear ();
    cout << "loadOFF" << endl;
      ifstream input (filename.c_str ());
      cout << "input file : " << filename << endl;
      if (!input)
          throw HGException ("Failing opening the file.");
      cout << "File loaded" << endl;
      string magic_word;
      input >> magic_word;
      if (magic_word != "OFF")
          throw HGException ("Not an OFF file.");

      // Get the number of Vertices and number of Triangles.
      unsigned int numOfVertices, numOfTriangles, numOfWhat;
      input >> numOfVertices >> numOfTriangles >> numOfWhat;

      // Get all the Vertices.
      for (unsigned int i = 0; i < numOfVertices; i++) {
          Vec3Df pos;
          Vec3Df col;
          input >> pos;
          vertices.push_back (Vertex (pos, Vec3Df (1.0, 0.0, 0.0)));
      }

      // Get all the Triangles.
      for (unsigned int i = 0; i < numOfTriangles; i++) {
          unsigned int polygonSize;
          input >> polygonSize;
          vector<unsigned int> index (polygonSize);
          for (unsigned int j = 0; j < polygonSize; j++)
              input >> index[j];
          for (unsigned int j = 1; j < (polygonSize - 1); j++)
              triangles.push_back (Triangle (index[0], index[j], index[j+1]));
      }

      input.close ();
      recomputeSmoothVertexNormals (0);
}