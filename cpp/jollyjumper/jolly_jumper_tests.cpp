#include "jolly_jumper.cpp"
#include <gtest/gtest.h>

TEST(JollyJumperTest, OnlyOneElement) {
  char line[2];
  strcpy(line, "1");
  ASSERT_TRUE(isJollyJumper(line));
}

TEST(JollyJumperTest, TwoElements) {
  char line[4];
  strcpy(line, "1 3");
  ASSERT_TRUE(isJollyJumper(line));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
