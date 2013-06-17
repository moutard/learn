#ifndef GRID_TEMPLATE_H
#define GRID_TEMPLATE_H

#include <vector>
using namespace std;

/**
 * Square grid of int.
 */
template <typename T>

class GridTemplate {
  public:
    GridTemplate();
    GridTemplate(unsigned int size, T _default);
    ~GridTemplate();
    unsigned int getSize();
    vector<vector<T> > get();
  private:
    unsigned int size;
    vector<vector<T> > grid;
};


template<typename T>
unsigned int GridTemplate<T>::getSize() {
  return size;
}

/**
 * @param size of the square grid
 * @param default value in the grid
 */
template<typename T>
GridTemplate<T>::GridTemplate(unsigned int _size, T _default) {
  size = _size;
  for (unsigned int i = 0; i < size; ++i) {
    grid.push_back(vector<int>());
    for (unsigned int j = 0; j < size; ++j) {
      grid[i].push_back(_default);
    }
  }
};

template<typename T>
vector<vector<T> > GridTemplate<T>::get() {
  return grid;
};

template<typename T>
GridTemplate<T>::~GridTemplate(){
  for (unsigned int i = 0; i < size; ++i) {
    grid[i].clear();
  }
};
#endif
