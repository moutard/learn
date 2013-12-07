#ifndef WALL_H
#define WALL_H

class Wall {

  public:
  double _min;
  double _max;
  Wall(double a_x, double a_y, double b_x, double b_y);
  bool fitHole(double a, double b, double c,
      double u, double v, double w);
  const double getMin() const {return _min;}
};
#endif
