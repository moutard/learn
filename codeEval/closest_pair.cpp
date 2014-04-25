#include <string>

class Point {
  public:
    Point(unsigned int x, unsigned int y);
  private:
    unsigned int _x;
    unsigned int _y;
};

Point::Point(unsigned int x, unsigned int y) : _x(x), _y(y) {}

Point pointFactory(std::string line) {
  return Point(0,0);
}

int main(int argc, char * argv[]) {
  return 0;
}
