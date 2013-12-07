#include "wall.h"
#include "brick.h"
#include "house.h"
#include <gtest/gtest.h>

using namespace std;

TEST(Wall, declareWall) {
  cout << "declare wall" << endl;
  Wall w; // declare w a Wall and call the default constructor. i.e. declare and instanciate.
  SUCCEED();
}

TEST(Wall, instanciateWall) {
  cout << "instanciate wall" << endl;
  Wall w(); // !! SEE THIS AS A FUNCTION DECLARATION
  // warning: empty parentheses interpreted as a function declaration [-Wvexing-parse]
  SUCCEED();
}

TEST(Brick, declareBrick) {
  Brick b; // the compiler creates for you an empty constructor.
  SUCCEED();
}

TEST(House, house_has_no_default_constructor) {
  House h; // the compiler creates for you an empty constructor.
  // val is not zeroed.
  cout << h.val << endl;
  SUCCEED();
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
