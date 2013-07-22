#include <iostream>
template <typename T>

class MyQueue {
  public:
    MyQueue();
    ~MyQueue();
    bool empty();
    bool full();
    int getLength();
    void enqueue(T element);
    T dequeue();
  private:
    int begin;  // index of the first element added in the queue.
    int end;    // index of the last  element added in the queue.
    int length;
    T * tab;
};

template <typename T>
MyQueue<T>::MyQueue() : begin(-1), end(-1), length(2) {
  // We need to begin at length = 2, to avoid problem when there is only one
  // box. Indeed if length = 1, (e = 0 , b = 0 we can not differenciate full and
  // empty !)
  tab = new T[2];
}

template <typename T>
MyQueue<T>::~MyQueue() {
  delete[] tab;
}

template <typename T>
inline bool MyQueue<T>::empty() {
  return (begin == -1);
}

template <typename T>
inline bool MyQueue<T>::full() {
  return (((end + 1) % length) == begin);
}

template <typename T>
inline int MyQueue<T>::getLength() {
  return length;
}

template <typename T>
void MyQueue<T>::enqueue(T element) {
  if(!full()) {
    // If not full just add the element in the next available space, and increase end.
    if(empty()) {begin = 0;}
    end = (end + 1) % length;
    tab[end] = element;
  } else {
    // If full create a new array of size 2*n, copy the element at the begining
    T * new_tab = new T[2*length];
    for(int i = 0; i < length; ++i) {
      new_tab[i] = tab[(i+begin) % length];
    }
    delete[] tab;
    // ??
    tab = new_tab;
    begin = 0;
    end = length - 1;
    length *= 2;
    // add the element after having more space.
    end += 1;
    tab[end] = element;
  }
}

template <typename T>
T MyQueue<T>::dequeue() {
  if(!empty()){
    T result = tab[begin];
    // that is the last element to dequeue
    if(begin == end) {
      begin = -1;
      end = -1;
    } else {
      begin += 1;
    }
    return result;
  } else {
    throw 20;
    std::cout << "Empty queue" << std::endl;
  }
}
