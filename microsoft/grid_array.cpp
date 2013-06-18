#include "grid_array.h"

GridArray::GridArray(unsigned int _size, int _default /*= 0*/) {
  size = _size;
  grid = new int*[size];
  for (unsigned int i = 0; i < size; ++i) {
    grid[i] = new int[size];
    for(unsigned int j = 0; j < size; ++j) {
      grid[i][j] = _default;
    }
  }
};

GridArray::~GridArray() {
  for(unsigned int i = 0; i < size; ++i) {
    delete[] grid[i];
  }
  delete[] grid;
};

unsigned int GridArray::getSize() {
  return size;
};

int GridArray::getElement(unsigned int x, unsigned int y) {
  return grid[x][y];
};

void GridArray::setElement(unsigned int x, unsigned int y, int _value) {
  grid[x][y] = _value;
};
