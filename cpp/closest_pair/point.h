#include <iostream>

#ifndef POINT_H
#define POINT_H


class Point {
  public:
    Point(unsigned int x, unsigned int y);
    unsigned int getX();
  private:
    unsigned int x, y;
};

#endif // POINT_H
