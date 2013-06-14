#ifndef SQUARE_H
#define SQUARE_H

/**
 * Shape is an abstract pure base class, that is used to
 * understand.
 */
class Square : public Shape {
  public:
    Square(int size);
    ~Square();
    int getSize();
  private:
    int size;
};

#endif // SQUARE_H
