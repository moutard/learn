#include "my_stack.h"
#include <gtest/gtest.h>

TEST(MyStack, Init) {
  MyStack<int> * q = new MyStack<int>();
  delete q;
  SUCCEED();
}

TEST(MyStack, Init_getLength) {
  MyStack<int> * q = new MyStack<int>();
  ASSERT_EQ(2, q->getLength());
  delete q;
}

TEST(MyStack, Init_empty) {
  MyStack<int> * q = new MyStack<int>();
  ASSERT_TRUE(q->empty());
  delete q;
}

TEST(MyStack, Init_full) {
  MyStack<int> * q = new MyStack<int>();
  ASSERT_FALSE(q->full());
  delete q;
}

TEST(MyStack, push) {
  MyStack<int> * q = new MyStack<int>();
  q->push(1);
  ASSERT_FALSE(q->full());
  q->push(2);
  ASSERT_TRUE(q->full());
  q->push(3);
  ASSERT_FALSE(q->full());
  q->push(4);
  ASSERT_TRUE(q->full());
  q->push(5);
  ASSERT_FALSE(q->full());

  delete q;
}

TEST(MyStack, pop_empty) {
  MyStack<int> * q = new MyStack<int>();
  ASSERT_ANY_THROW(q->pop());
  ASSERT_ANY_THROW(q->pop());
  ASSERT_ANY_THROW(q->pop());
  delete q;
}

TEST(MyStack, pop_in_order) {
  MyStack<int> * q = new MyStack<int>();
  q->push(1);
  q->push(2);
  q->push(3);
  ASSERT_EQ(3, q->pop());
  ASSERT_EQ(2 , q->pop());
  ASSERT_EQ(1 , q->pop());
  ASSERT_ANY_THROW(q->pop());
  delete q;
}

TEST(MyStack, pop_not_in_order) {
  MyStack<int> * q = new MyStack<int>();
  q->push(1);
  q->push(2);
  ASSERT_EQ(2, q->pop());
  q->push(3);
  q->push(4);
  ASSERT_EQ(4 , q->pop());
  ASSERT_EQ(3 , q->pop());
  q->push(5);
  ASSERT_EQ(5, q->pop());
  ASSERT_EQ(1 , q->pop());
  ASSERT_ANY_THROW(q->pop());
  delete q;
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
