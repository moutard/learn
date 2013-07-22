#include <iostream>
template <typename T>

class MyStack {
  public:
    MyStack();
    ~MyStack();
    bool empty();
    bool full();
    int getLength();
    void push(T element);
    T pop();
  private:
    int end;    // index of the last  element added in the queue.
    int length;
    T * tab;
};

template <typename T>
MyStack<T>::MyStack() : end(-1), length(2) {
  // We need to begin at length = 2, to avoid problem when there is only one
  // box. Indeed if length = 1, (e = 0 , b = 0 we can not differenciate full and
  // empty !)
  tab = new T[2];
}

template <typename T>
MyStack<T>::~MyStack() {
  delete[] tab;
}

template <typename T>
inline bool MyStack<T>::empty() {
  return (end == -1);
}

template <typename T>
inline bool MyStack<T>::full() {
  return (end + 1)  == length;
}

template <typename T>
inline int MyStack<T>::getLength() {
  return length;
}

template <typename T>
void MyStack<T>::push(T element) {
  if(!full()) {
    // If not full just add the element in the next available space, and increase end.
    end = (end + 1);
    tab[end] = element;
  } else {
    // If full create a new array of size 2*n, copy the element at the begining
    T * new_tab = new T[2*length];
    for(int i = 0; i < length; ++i) {
      new_tab[i] = tab[i];
    }
    delete[] tab;
    // ??
    tab = new_tab;
    end = length - 1;
    length *= 2;
    // add the element after having more space.
    end += 1;
    tab[end] = element;
  }
}

template <typename T>
T MyStack<T>::pop() {
  if(!empty()){
    T result = tab[end];
    // that is the last element to dequeue
    end -= 1;
    return result;
  } else {
    throw 20;
    std::cout << "Empty stack" << std::endl;
  }
}
