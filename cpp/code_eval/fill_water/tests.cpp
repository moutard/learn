#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Digit, simpleDigitIsArmstrong) {
  ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
