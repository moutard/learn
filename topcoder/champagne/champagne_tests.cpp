#include "champagne.cpp"
#include <gtest/gtest.h>
// PROBLEM WITH TEST BECAUSE amount is global and not reset !!
TEST(SquareRootTest, SmallValues) {
  Champagne * c = new Champagne();

  // Expect_EQ iq used to compare c++ strings according to gtest documentation.
  EXPECT_EQ("1/2", c->howMuch(1, 1, 1));
  EXPECT_EQ("0/1", c->howMuch(2, 2, 2));
  EXPECT_EQ("1/4", c->howMuch(2, 2, 3));
  EXPECT_EQ("1/8", c->howMuch(3, 4, 7));
 }
TEST(SquareRootTest, BigValues) {
  Champagne * c = new Champagne();
  EXPECT_EQ("5581/131072", c->howMuch(20, 204, 300));
  EXPECT_EQ("663/262144", c->howMuch(20, 204, 299));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
