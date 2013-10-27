#include "grid.h"

/**
 * @param size of the square grid
 * @param default value in the grid
 */
Grid::Grid(unsigned int _size, int _default) {
  size = _size;
  for (unsigned int i = 0; i < size; ++i) {
    grid.push_back(vector<int>());
    for (unsigned int j = 0; j < size; ++j) {
      grid[i].push_back(_default);
    }
  }
};

vector<vector<int> > Grid::get() {
  return grid;
};

unsigned int Grid::getSize() {
  return size;
}

Grid::~Grid(){
  for (unsigned int i = 0; i < size; ++i) {
    grid[i].clear();
  }
};
