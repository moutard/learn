#include "shape.h"
#include "square.h"
#include <gtest/gtest.h>

TEST(SquareRootTest, NegativeNos) {
  Square * s = new Square(5);
  ASSERT_EQ(5, s->getSize());
  delete s;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
