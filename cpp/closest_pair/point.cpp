#include "point.h"

/**
 * Default constructor.
 */
Point::Point(unsigned int _x, unsigned int _y) {
  x = _x;
  y = _y;
};

unsigned int Point::getX(){
  return x;
};
