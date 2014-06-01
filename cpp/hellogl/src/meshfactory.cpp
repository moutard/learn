#include "meshfactory.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "utils/hgexception.h"

using namespace std;

MeshFactory::MeshFactory()
{
}

string MeshFactory::findExtension(const string & filename) {
    stringstream ss(filename);
    string extension;
    while (getline(ss, extension, '.')) {
        // do nothing
    }
    return extension;
}

void MeshFactory::fromFile(const string & filename, Mesh * mesh) {
    string extension  = findExtension(filename);
    if (extension.compare("off") == 0) {
        cout << "Valid file. off extension detected." << endl;
        fromOffFile(filename, mesh);
    } else {
        cout << "Not Valid file. extension unknown: " << extension << endl;
        cout << "Available extensions are: [.off]" << endl;
    }
}

/**
 * @brief MeshFactory::fromOffFile
 * @param filename
 * @return
 * An .off file contains
 * - the first line the "OFF"
 * - the second line contains the number of vertices, and triangles.
 * - then all the lines are in order
 *  the vertices : x y z
 *  the polygones: polygone size + index to the corresponding vertices
 */
void MeshFactory::fromOffFile(const string & filename, Mesh * mesh) {

    ifstream input (filename.c_str ());
    if (!input.is_open()) {
        cout << filename << endl;
          throw HGException ("Failing opening the file.");
    }

    // the name of the extension appears at the beginning of the files.
    string magic_word;
    input >> magic_word;
    if (magic_word != "OFF")
        throw HGException ("Not an OFF file.");

    // Get the number of Vertices and number of Triangles.
    unsigned int numOfVertices, numOfTriangles, numUnused;
    input >> numOfVertices >> numOfTriangles >> numUnused;

    mesh->reserve(numOfVertices, numOfTriangles);

    // Get all the Vertices.
    for (unsigned int i = 0; i < numOfVertices; ++i) {
        Vec3Df pos;
        input >> pos;
        mesh->pushVertex(Vertex (pos, Vec3Df (1.0, 0.0, 0.0)));
    }

    // Get all the Triangles.
    for (unsigned int i = 0; i < numOfTriangles; i++) {
        unsigned int polygonSize;
        input >> polygonSize;
        vector<unsigned int> index (polygonSize);
        for (unsigned int j = 0; j < polygonSize; j++) {
            input >> index[j];
        }
        // Decompose any polygones into triangles.
        for (unsigned int j = 1; j < (polygonSize - 1); j++) {
            mesh->pushTriangle(Triangle (index[0], index[j], index[j+1]));
        }
    }

    input.close ();
    mesh->recomputeSmoothVertexNormals(0);
}
