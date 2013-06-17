#include "square.h"
#include "grid.h"
#include "grid_template.h"
#include "template.h"
#include <gtest/gtest.h>

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


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
