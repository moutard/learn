#include <climits>
#include "heap.h"

Heap::Heap(){};
Heap::Heap(unsigned int _size){
  size = _size;
  fill = 0;
  heap = new unsigned int[_size];
  for(unsigned int i = 0; i < _size; ++i){
    heap[i] = UINT_MAX;
  }
};

Heap::~Heap(){
  delete[] heap;
};

void Heap::insert(unsigned int element) {
  if(fill < size) {
    ++fill;
    heap[fill] = element;
  } else if(element > min()) {
    // we don't need the min anymore.
    heap[0] = element;
    decrease();
  }
};

inline unsigned int Heap::min(){
  return heap[0];
};

void Heap::decrease() {
  unsigned int i = 0;

  while(heap[i] > heap[2*i + 1] && heap[i] > heap[2*i + 2]) {
    unsigned int min_index;
    if(heap[2*i + 1] < heap[2*i + 2]) {
      min_index = 2*i + 1;
    } else {
      min_index = 2*i + 2;
    }

    // switch the new min.
    unsigned int temp = heap[i];
    heap[i] = heap[min_index];
    heap[min_index] = temp;
    // increase i
    i = min_index;
  }
};


