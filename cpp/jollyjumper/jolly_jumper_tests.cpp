#include "jolly_jumper.cpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

TEST(JollyJumperTest, OnlyOneElement) {
  string line("1");
  vector<int> v;
  parseLineInVector(line, v);
  EXPECT_EQ(1, v[0]);
}

TEST(JollyJumperTest, TwoElements) {
  string line("1 3");
  vector<int> v;
  parseLineInVector(line, v);
  for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
    cout << *it << endl;
  }
  EXPECT_EQ(3, v[1]);
}

TEST(JollyJumperTest, OnlyThreeSpaces) {
  string line("   ");
  vector<int> v;
  parseLineInVector(line, v);
  for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
    cout << *it << endl;
  }
  EXPECT_EQ(v.size(), 0);
}

TEST(JollyJumperTest, TrailingWhiteSpace) {
  string line("1 3   ");
  vector<int> v;
  parseLineInVector(line, v);
  for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
    cout << *it << endl;
  }
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(3, v[1]);
}

TEST(JollyJumperTest, isNotJolly) {
  string line("1 3");
  vector<int> v;
  parseLineInVector(line, v);
  ASSERT_FALSE(isJollyJumper(v));
}

TEST(JollyJumperTest, isJolly) {
  string line("1 4 2 3 ");
  vector<int> v;
  parseLineInVector(line, v);
  ASSERT_TRUE(isJollyJumper(v));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
