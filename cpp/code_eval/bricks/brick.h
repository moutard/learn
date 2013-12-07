#include <string>

using namespace std;

#ifndef BRICK_H
#define BRICK_H

Brick {
  double a, b, c, u, v, w, id;


  public:
  Brick(double _a, double _b, double _c, double _u, double _v, double _w, double _id):
  a(_a), b(_b), c(_c), u(_u), v(_v), w(_w), id(_id) {

  };
  double getId() {
    return id;
  };
};
#endif
