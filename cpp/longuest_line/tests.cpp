#include "heap.h"
#include <climits>
#include <gtest/gtest.h>

TEST(Heap, initialize) {
  Heap * h = new Heap(5);
  ASSERT_EQ(UINT_MAX, h->min());
  delete h;
}

TEST(Grid, insert_until_fill_inferior_size) {
  Heap * h = new Heap(5);
  h->insert(10);
  ASSERT_EQ(10, h->min());
  h->insert(5);
  ASSERT_EQ(5, h->min());
  h->insert(9);
  ASSERT_EQ(5, h->min());
  h->insert(8);
  ASSERT_EQ(8, h->min());
  h->insert(4);
  ASSERT_EQ(4, h->min());
  delete h;
}

TEST(Example, insert_more_than_size) {
  Heap * h = new Heap(3);
  h->insert(10);
  h->insert(5);
  h->insert(9);
  h->insert(4);
  h->insert(8);
  ASSERT_EQ(4, h->min());

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
