#ifndef GRID_ARRAY_H
#define GRID_ARRAY_H

class GridArray {
  public:
    GridArray();
    GridArray(unsigned int _size, int _default = 0);
    ~GridArray();
    unsigned int getSize();
    int getElement(unsigned int x, unsigned int y);
    void setElement(unsigned int x, unsigned int y, int _value);
  private:
    unsigned int size;
    int ** grid;
};
#endif
