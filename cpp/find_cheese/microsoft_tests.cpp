#include "maze.h"
#include <gtest/gtest.h>
using namespace std;

TEST(Direction, oppositeDirection) {
  ASSERT_EQ(1, oppositeDirection(3));
  ASSERT_EQ(2, oppositeDirection(4));
  ASSERT_EQ(3, oppositeDirection(1));
  ASSERT_EQ(4, oppositeDirection(2));
}

TEST(Maze, init_maze) {
  Maze * maze = new Maze();
  SUCCEED();
  delete maze;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
