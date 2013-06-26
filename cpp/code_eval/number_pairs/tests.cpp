#include "digit.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Digit, simpleDigitIsArmstrong) {
  string s = "6";
  ASSERT_TRUE(isArmstrongNumber(s));
}

TEST(Digit, zero) {
  string s = "0";
  ASSERT_TRUE(isArmstrongNumber(s));
}

TEST(Digit, isArmstrong) {
  string s = "153";
  ASSERT_TRUE(isArmstrongNumber(s));
}
TEST(Digit, notAmstrong) {
  string s = "351";
  ASSERT_FALSE(isArmstrongNumber(s));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
