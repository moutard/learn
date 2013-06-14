#include <iostream>

#ifndef SHAPE_H
#define SHAPE_H

/**
 * Shape is an abstract pure base class, that is used to
 * understand.
 */
class Shape{
  public:
    Shape();
    Shape(int _id);
    virtual ~Shape() = 0;
  private:
    int id;
};

#endif // SHAPE_H
