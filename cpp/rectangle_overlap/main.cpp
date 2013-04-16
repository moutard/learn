#include <algorithm>    // std::max
#include <iostream>
using namespace std;

class Point {
  public:
  int x;
  int y;
  Point();
  Point(int _x, int _y){
    x = _x;
    y = _y;
  };
};

class Rectangle {
  public:
  Point *ul;
  Point *lr;
  Rectangle(Point * _ul, Point * _lr){
    ul = _ul;
    lr = _lr;
  }
  int width(){return lr->x - ul->x;};
  int height(){return ul->y - lr->y;};
  ~Rectangle(){
    delete ul;
    delete lr;
  };
};

Rectangle *boundingbox(Rectangle *r1, Rectangle *r2){
  Point *ul = new Point(min(r1->ul->x, r2->ul->x), max(r1->ul->y, r2->ul->y));
  Point *lr = new Point(max(r1->lr->x, r2->lr->x), min(r1->lr->y, r2->ul->y));
  return new Rectangle(ul, lr);
};

bool overlap(Rectangle *r1, Rectangle *r2){
  bool overlap = true;
  Rectangle *bbox = boundingbox(r1, r2);
  overlap = (bbox->width() <= (r1->width() + r2->width()))
    && (bbox->height() <= (r1->height() + r2->height()));
  delete bbox;
  return overlap;
};

int main(int argc, char **argv){
  Point *ul1 = new Point(0,2);
  Point *lr1 = new Point(2,0);
  Rectangle *r1 = new Rectangle(ul1, lr1);

  Point *ul2 = new Point(0,2);
  Point *lr2 = new Point(2,0);
  Rectangle *r2 = new Rectangle(ul2, lr2);

  bool result = overlap(r1, r2);
  cout << result << endl;
  delete r1;
  delete r2;
  return 0;
};

/*
Given 2 rectangles by their upper-left corner and lower-right corner. Both
rectangle's edges will always be parallel to the x or y axis. Write a function
to determine wheter the two rectangles overlap.

Overlap condition is very difficult,
but non overlapping condition is more straightforward.

A and B 2 rectanlges, they do not overlap if A over B or A below B, or A is to
the left B or A is to the right of B.
*/
