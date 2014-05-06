#include <string>
#include <iostream>
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <stdlib.h>// atoi
#include <vector>
#include <math.h>
#include <algorithm>
#include <cfloat>
#include <iomanip>
class Point {
  public:
    Point(unsigned int x, unsigned int y);
    std::ostream& print(std::ostream& os) const;
    unsigned int x() {return _x;};
    unsigned int y() {return _y;};
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

float minDistanceSquare (std::vector<Point> & points, unsigned int start, unsigned int end) {
  if (end == start) {
    // Should never happened.
    return FLT_MAX;
  }
  float minDistance = distance(points[start], points[start+1]);
  for (unsigned int i = start; i < end; ++i) {
    for (unsigned int j = i+1; j < end; ++j) {
      float currentDistance = distance(points[i], points[j]);
      if (currentDistance < minDistance) {
        minDistance = currentDistance;
      }
    }
  }
  return minDistance;
}

void median(std::vector<Point> &v, unsigned int n,  bool x = true) {
  if (x) {
    nth_element(v.begin(), v.begin()+n, v.end(), predicateX);
  } else {
    nth_element(v.begin(), v.begin()+n, v.end(), predicateY);
  }
}

float minBorderDistance(std::vector<Point> & points, float delta) {
  float minDistance = delta;
  std::sort(points.begin(), points.end(), predicateY);
  // Only perform 6 computation macimum.
  for (unsigned int i = 0; i < points.size(); ++i) {
    for (unsigned int j = i+1; j < points.size()
        && points[j].y() - points[i].y() < minDistance; ++j) {
       if (distance(points[i], points[j])) {
        minDistance = distance(points[i], points[j]);
      }
    }
  }
  return minDistance;
}

float minDistance (std::vector<Point> & points, unsigned int start, unsigned int end) {
  float result;

  if (end - start <= 4) {
    result = minDistanceSquare(points, start, end);
  } else {
    unsigned int medianIndex = (end-start)/2;
    median(points, medianIndex);
    float delta = std::min(
        minDistance(points, start, start + medianIndex),
        minDistance(points, start + medianIndex + 1, end));
    // compute border minDistance
    result = minBorderDistance(points, delta);
  }
  return sqrt(result);
}
void formatResult(float f) {
  if (f > 10000) {
    std::cout << "INFINITY" << std::endl;
  } else {
    std::cout << std::fixed << std::setprecision(4) << f << std::endl;
  }
}

int main(int argc, char * argv[]) {

  std::vector<Point> sky;
  std::ifstream oFile;
  oFile.open(argv[1], std::ios::in);
  if (oFile.is_open()) {
    std::string line;
    while(getline(oFile, line)) {
      unsigned int K = atoi(line.c_str());
      if (K > 0) {
        for (unsigned int i = 0; i < K; ++i) {
          getline(oFile, line);
          sky.push_back(pointFactory(line));
        }
        float m = minDistance(sky, 0, sky.size() - 1);
        formatResult(m);
        sky.clear();
        getline(oFile, line);
      }
    }
    oFile.close();
  }
  return 0;
}
