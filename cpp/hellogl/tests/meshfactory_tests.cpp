#include <gtest/gtest.h>
#include <string>
#include "../src/meshfactory.h"
#include "../src/mesh.h"
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
  Mesh mesh;
  const string input("../models/ground.off");
  f.fromFile(input, mesh);
  cout << mesh.getTriangles().size() << endl;
  ASSERT_EQ(2, mesh.getTriangles().size());
  ASSERT_EQ(4, mesh.getVertices().size());
}

