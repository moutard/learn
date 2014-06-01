#include <gtest/gtest.h>
#include <string>
#include "../src/meshfactory.h"
#include "../src/core/mesh.h"
#include "../src/core/triangle.h"
#include "../src/core/vertex.h"
#include "../src/core/vec3d.h"
using namespace std;

TEST(MeshFactory, findExtensionFileName) {
  MeshFactory f;
  const string input("test.off");
  string expected("off");
  string actual(f.findExtension(input));
  ASSERT_EQ(expected, actual);
}

TEST(MeshFactory, findExtensionPathToFile) {
  MeshFactory f;
  const string input("/usr/rmoutard/test.off");
  const string expected("off");
  ASSERT_EQ(expected, f.findExtension(input));
}

TEST(MeshFactory, findExtensionWithManyDot) {
  MeshFactory f;
  const string input("/usr/rmoutard/test.path.test.off");
  string expected("off");
  ASSERT_EQ(expected, f.findExtension(input));
}

TEST(MeshFactory, fromFile) {
  MeshFactory f;
  Mesh * mesh = new Mesh();
  const string input("../models/ground.off");
  f.fromFile(input, mesh);
  ASSERT_EQ(2, mesh->getTriangles().size());
  ASSERT_EQ(4, mesh->getVertices().size());
  delete mesh;
}

TEST(MeshFactory, fromFileTriangle) {
  MeshFactory f;
  Mesh * mesh = new Mesh();
  const string input("../models/ground.off");
  f.fromFile(input, mesh);
  Triangle t0(0, 1, 2);
  Triangle t1(0, 2, 3);
  Triangle & _t0 = mesh->getTriangles()[0];
  Triangle & _t1 = mesh->getTriangles()[1];
  ASSERT_EQ(_t0, t0);
  ASSERT_EQ(_t1, t1);
  delete mesh;
}

TEST(MeshFactory, fromFilePosition) {
  MeshFactory f;
  Mesh * mesh = new Mesh();
  const string input("../models/ground.off");
  f.fromFile(input, mesh);
  cout << mesh->getTriangles().size() << endl;

  Triangle & t = mesh->getTriangles()[0];
  float x_input = mesh->getVertices()[t.getVertex(0)].getPos()[0];
  float x_expected = 1.95251;
  ASSERT_EQ(x_input, x_expected);
  delete mesh;
}


