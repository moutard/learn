#include "wall.h"
#include <stdlib.h>
#include <algorithm>    // std::max // std::swap
#include <cmath>
#include <string>
using namespace std;

Wall::Wall (double a_x, double a_y, double b_x, double b_y) {
  double x = std::abs(a_x - b_x);
  double y = std::abs(a_y - b_y);
  _min = min(x, y);
  _max = max(x, y);
}

bool Wall::fitHole (double a, double b, double c,
    double u, double v, double w) {
  double i1 = std::abs(a - u);
  double i2 = std::abs(b - v);
  double i3 = std::abs(c - w);

  // Sort the 3 values.
  // i1 will be the lowest number
  // i2 middle
  // i3 is the highest
  if (i2 > i3)
    swap(i2, i3);
  if (i1 > i2)
    swap(i1, i2);
  if (i2 > i3)
    swap(i2, i3);

  return ((i1 <= _min) && (i2 <= _max));
}
