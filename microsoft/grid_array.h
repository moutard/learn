#ifndef GRID_ARRAY_H
#define GRID_ARRAY_H
#include <iostream>
#include <fstream>
using namespace std;

class GridArray {
  public:
    GridArray();
    GridArray(unsigned int _size, int _default = 0);
    GridArray(ifstream  & _input_file);
    ~GridArray();
    unsigned int getSize();
    int getElement(unsigned int x, unsigned int y);
    void setElement(unsigned int x, unsigned int y, int _value);
    void print();
    int findShortestPath();
  private:
    unsigned int size;
    int ** grid;
};
#endif