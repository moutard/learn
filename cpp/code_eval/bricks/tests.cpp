#include "wall.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Wall, defaultConstructorWall) {

  Wall w;
  SUCCEED();
}


TEST(Wall, createWall) {
  Wall w(3.0, 4.0, 5.0, 6.0);
  ASSERT_EQ(w._min, 2.0);
  ASSERT_EQ(w._max, 2.0);
}

TEST(Wall, createWallForMin) {
  Wall w(0.0, 0.0, 5.0, 6.0);
  ASSERT_EQ(w._min, 5.0);
  ASSERT_EQ(w._max, 6.0);
}

TEST(Wall, okForHole_1) {
  Wall w(0.0, 0.0, 5.0, 6.0);
  ASSERT_TRUE(w.fitHole(
        0.0, 0.0, 0.0,
        1.0, 1.0, 1.0
        )
  );
}

TEST(Wall, okForHole_2) {
  Wall w(0.0, 0.0, 5.0, 6.0);
  ASSERT_TRUE(w.fitHole(
        0.0, 0.0, 0.0,
        7.0, 1.0, 1.0
        )
  );
}

TEST(Wall, notOkForHole_1) {
  Wall w(0.0, 0.0, 5.0, 6.0);
  ASSERT_FALSE(w.fitHole(
        0.0, 0.0, 0.0,
        7.0, 1.0, 7.0
        )
  );
}

/**
 * Test example
 */
TEST(Wall, example_okForHole_1) {
  Wall w(4.0, 3.0, 3.0, -3.0);
  ASSERT_TRUE(w.fitHole(
        10.0, 9.0, 4.0,
        9.0, 4.0, 2.0
        )
  );
}

TEST(Wall, example_okForHole_2) {
  Wall w(-1.0, -5.0, 5.0, -2.0);
  ASSERT_TRUE(w.fitHole(
        4.0, 7.0, 8.0,
        2.0, 9.0, 0.0
        )
  );
  ASSERT_TRUE(w.fitHole(
        0.0, 7.0, 1.0,
        5.0, 9.0, 8.0
        )
  );

}

TEST(Wall, example_okForHole_3) {
  Wall w(-4.0, -5.0, -5.0, -3.0);
  ASSERT_FALSE(w.fitHole(
        4.0, 8.0, 6.0,
        0.0, 9.0, 2.0
        )
  );
  ASSERT_FALSE(w.fitHole(
        8.0, -1.0, 3.0,
        0.0, 5.0, 5.0
        )
  );

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
