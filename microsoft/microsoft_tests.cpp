#include "square.h"
#include "grid.h"
#include "grid_template.h"
#include "grid_array.h"
#include "template.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
using namespace std;

TEST(Square, getSize) {
  Square * s = new Square(5);
  ASSERT_EQ(5, s->getSize());
  delete s;
}

TEST(Grid, init) {
  Grid * g = new Grid(5, 0);
  ASSERT_EQ(5, g->getSize());
  delete g;
}

TEST(Example, init) {
 // GridTemplate<int> * g = new GridTemplate<int>(5, 0);
 // ASSERT_EQ(5, g->getSize());
 // delete g;
  Exemple<int> A(3);
  ASSERT_EQ(3, A.Get());
}

TEST(GridTemplate, init) {
  GridTemplate<int> * g = new GridTemplate<int>(5, 0);
  ASSERT_EQ(5, g->getSize());
  delete g;
}


TEST(GridArray, init) {
  GridArray * g = new GridArray(5);
  ASSERT_EQ(5, g->getSize());
  ASSERT_EQ(0, g->getElement(0,0));
  g->setElement(3,4, 42);
  ASSERT_EQ(42, g->getElement(3,4));
  delete g;
}

TEST(GridArray, initWithFile) {
  ifstream myfile ("example.txt");
  if (myfile.is_open()) {
    GridArray * g = new GridArray(myfile);
    ASSERT_EQ(4, g->getSize());
    ASSERT_EQ(0, g->getElement(0,0));
    ASSERT_EQ(3, g->getElement(1, 0));
    delete g;
  }
  else {
    cout << "Unable to open file";
    FAIL();
  }
  myfile.close();
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
