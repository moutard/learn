#include <string>
#include <iostream>
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <stdlib.h>// atoi
#include <vector>
#include <math.h>
#include <algorithm>


class Point {
  public:
    Point(unsigned int x, unsigned int y);
    std::ostream& print(std::ostream& os) const;
  private:
    friend float distance(const Point& p1, const Point& p2);
    friend bool predicateX(const Point & p1, const Point & p2);
    friend bool predicateY(const Point & p1, const Point & p2);
    unsigned int _x;
    unsigned int _y;
};

bool predicateX(const Point & p1, const Point & p2) { return (p1._x < p2._x);}
bool predicateY(const Point & p1, const Point & p2) { return (p1._y < p2._y);}


Point::Point(unsigned int x, unsigned int y) : _x(x), _y(y) {}

std::ostream& Point::print(std::ostream& os) const {
  os << "P { x: " << _x << " y: " << _y << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Point & p) {
  return p.print(os);
}

Point pointFactory(std::string & line) {
  std::string x, y;
  std::stringstream ss(line);
  std::getline(ss, x, ' ');
  std::getline(ss, y, ' ');
  return Point(atoi(x.c_str()), atoi(y.c_str()));
}

float distance(const Point& p1, const Point& p2) {
  return (p1._x - p2._x)*(p1._x - p2._x)
    + (p1._y - p2._y)*(p1._y - p2._y) ;
}

float minDistanceSquare (std::vector<Point> & points) {
  if (points.size() < 2) {
    return 0;
  }
  std::vector<Point>::iterator it = points.begin();
  std::vector<Point>::iterator it2 = points.begin();
  it2++;

  float minDistance = distance(*it, *it2);
  for (it = points.begin(); it != points.end(); ++it) {
    for (it2 = points.begin(); it2 != points.end(); ++it2) {
      if (it != it2) {
        float currentDistance = distance(*it, *it2);
        if (currentDistance < minDistance) {
          minDistance = currentDistance;
        }
      }
    }
  }
  return sqrt(minDistance);
}

void median(std::vector<Point> &v, unsigned int n,  bool x = true) {
  if (x) {
    nth_element(v.begin(), v.begin()+n, v.end(), predicateX);
  } else {
    nth_element(v.begin(), v.begin()+n, v.end(), predicateY);
  }
}

float minDistance (std::vector<Point> & points, unsigned int start, unsigned int end) {
  float result;
  if (end - start <= 10) {
    result = minDistanceSquare(points);
    std::cout << "Leaf min Distance:" << result << std::endl;
  } else {
    unsigned int medianIndex = (end-start) /2;
    median(points, medianIndex);
    result = std::min(
        minDistance(points, start, medianIndex),
        minDistance(points, medianIndex+1, end));
  }
  return result;
}

int main(int argc, char * argv[]) {

  std::vector<Point> sky;
  std::ifstream oFile;
  oFile.open(argv[1], std::ios::in);
  if (oFile.is_open()) {
    std::string line;
    while(getline(oFile, line)) {
      sky.push_back(pointFactory(line));
    }
    oFile.close();

  }
  std::cout<< minDistance(sky, 0, sky.size() - 1) << std::endl;
  return 0;
}
