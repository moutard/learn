#include <iostream>
#include "stdlib.h"

#ifndef HEAP_H
#define HEAP_H

class Heap {
  public:
  Heap();
  Heap(unsigned int size);
  ~Heap();
  void insert(unsigned int element);
  inline unsigned int min();
  void decrease();
  private:
    unsigned int size;
    unsigned int fill;
    unsigned int * heap;
};

#endif
