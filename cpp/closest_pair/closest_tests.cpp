#include "point.h"
#include "univers.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
using namespace std;

TEST(Square, getSize) {
  Point * p = new Point(5, 4);
  ASSERT_EQ(5, p->getX());
  delete p;
  SUCCEED();
}

TEST(Grid, init) {
  Univers * u = new Univers();
  u->loadFromFile("example.txt");
  delete u;
  SUCCEED();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
