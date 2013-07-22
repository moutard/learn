#include "my_queue.h"
#include <gtest/gtest.h>

TEST(MyQueue, Init) {
  MyQueue<int> * q = new MyQueue<int>();
  delete q;
  SUCCEED();
}

TEST(MyQueue, Init_getLength) {
  MyQueue<int> * q = new MyQueue<int>();
  ASSERT_EQ(2, q->getLength());
  delete q;
}

TEST(MyQueue, Init_empty) {
  MyQueue<int> * q = new MyQueue<int>();
  ASSERT_TRUE(q->empty());
  delete q;
}

TEST(MyQueue, Init_full) {
  MyQueue<int> * q = new MyQueue<int>();
  ASSERT_FALSE(q->full());
  delete q;
}

TEST(MyQueue, enqueue) {
  MyQueue<int> * q = new MyQueue<int>();
  q->enqueue(1);
  ASSERT_FALSE(q->full());
  q->enqueue(2);
  ASSERT_TRUE(q->full());
  q->enqueue(3);
  ASSERT_FALSE(q->full());
  q->enqueue(4);
  ASSERT_TRUE(q->full());
  q->enqueue(5);
  ASSERT_FALSE(q->full());

  delete q;
}

TEST(MyQueue, dequeue_empty) {
  MyQueue<int> * q = new MyQueue<int>();
  ASSERT_ANY_THROW(q->dequeue());
  ASSERT_ANY_THROW(q->dequeue());
  ASSERT_ANY_THROW(q->dequeue());
  delete q;
}

TEST(MyQueue, dequeue_in_order) {
  MyQueue<int> * q = new MyQueue<int>();
  q->enqueue(1);
  q->enqueue(2);
  q->enqueue(3);
  ASSERT_EQ(1, q->dequeue());
  ASSERT_EQ(2 , q->dequeue());
  ASSERT_EQ(3 , q->dequeue());
  ASSERT_ANY_THROW(q->dequeue());
  delete q;
}

TEST(MyQueue, dequeue_not_in_order) {
  MyQueue<int> * q = new MyQueue<int>();
  q->enqueue(1);
  q->enqueue(2);
  ASSERT_EQ(1, q->dequeue());
  q->enqueue(3);
  q->enqueue(4);
  ASSERT_EQ(2 , q->dequeue());
  ASSERT_EQ(3 , q->dequeue());
  q->enqueue(5);
  ASSERT_EQ(4 , q->dequeue());
  ASSERT_EQ(5 , q->dequeue());
  ASSERT_ANY_THROW(q->dequeue());
  delete q;
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
