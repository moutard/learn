#include "digit.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Digit, getSum) {
  string s = "23";
  ASSERT_EQ(5, getSum(s));
}
TEST(Digit, getSumOneDigit) {
  string s = "5";
  ASSERT_EQ(5, getSum(s));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
