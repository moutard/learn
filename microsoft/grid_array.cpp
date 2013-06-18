#include "grid_array.h"
#include <string>
#include <sstream>
using namespace std;

GridArray::GridArray(){
  size = 0;
};
/**
 * create an grid of size n*n fill with value 0.
 */
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

GridArray::GridArray(ifstream & _input_file) {
  int x = 0, y = 0;
  string line;
  if(_input_file.good()) {
    getline (_input_file, line);
    stringstream size_streamed_line(line);
    size_streamed_line >> size;
    cout << "Initialize grid with size : " << size << endl;
    // initialise the grid with default value.
    grid = new int*[size];
    for (unsigned int i = 0; i < size; ++i) {
      grid[i] = new int[size];
      for(unsigned int j = 0; j < size; ++j) {
        grid[i][j] = 0;
      }
    }
    // set element for each value.
    while (getline(_input_file, line)) {
      stringstream streamed_line(line);
      string token;
      int value;
      while(getline(streamed_line, token, ' ')) {
        istringstream my_value(token);
        my_value >> value;
        grid[x][y] = value;
        y++;
      }
      y = 0;
      x++;
    }
  }
  cout << "grid initalized" << endl;
  print();
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
  if(x < size && y < size){
    return grid[x][y];
  } else {
    cout << "boud limit." << endl;
  }
};

void GridArray::setElement(unsigned int x, unsigned int y, int _value) {
  grid[x][y] = _value;
};

void GridArray::print(){
  for (unsigned int i = 0; i < size; ++i) {
    for(unsigned int j = 0; j < size; ++j) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
};
