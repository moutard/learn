#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Vecteur {
  public:
    Vecteur(const Vecteur & p): x(p.x), y(p.y) {};
    Vecteur(const Vecteur & p1, const Vecteur & p2): x(p2.x - p1.x), y(p2.y - p1.y) {};
    Vecteur(float _x, float _y): x(_x), y(_y) {};
    ostream & print(ostream & os) const {
      return os << "P(x= " << x << " y= " << y << ")";
    };
    Vecteur & operator+= (const Vecteur & v) {
      x += v.x;
      y += v.y;
    };
    Vecteur & operator-= (const Vecteur & v) {
      x -= v.x;
      y -= v.y;
    };
    Vecteur & operator*= (float r) {
      x *= r;
      y *= r;
    };
    friend ostream & operator<<(ostream & os, const Vecteur & v);
    float x, y;
};

ostream & operator<< (ostream & os, const Vecteur & v) {
  return v.print(os);
}
const Vecteur operator+ (const Vecteur & v1, const Vecteur & v2) {
    Vecteur v(v1);
    v+=v2;
    return v;
}
const Vecteur operator- (const Vecteur & v1, const Vecteur & v2) {
    Vecteur v(v1);
    v -= v2;
    return v;
}
const Vecteur operator* (float r, const Vecteur & v) {
  Vecteur res(v);
  res*=r;
  return res;
}

int crossProduct (const Vecteur & v1, const Vecteur & v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

class Droite {
  public:
    Droite (Vecteur _origin, Vecteur _direction) : origin(_origin), direction(_direction) {}
    Vecteur origin, direction;
};

class Segment {
  public:
    Segment (Vecteur _v0, Vecteur _v1): origin(_v0), end(_v1) {}
    Vecteur origin, end;
};

class Block {
  public:
    Block (Vecteur _p0, Vecteur _p1): leftBottom(_p0), rightUp(_p1) {};
    float height() const {return rightUp.y - leftBottom.y;};
    float width() const {return rightUp.x - leftBottom.x;};
    Vecteur leftBottom, rightUp;
};

bool intersectSegments (const Segment & s1, const Segment & s2, Vecteur & result) {

  // See http://www.faqs.org/faqs/graphics/algorithms-faq/ for the formula
  float denominator = ((s1.end.x - s1.origin.x) * (s2.end.y - s2.origin.y)
        - (s1.end.y - s1.origin.y) * (s2.end.x - s2.origin.x));
  if (denominator != 0) {
    float r = ((s1.origin.y - s2.origin.y) * (s2.end.x - s2.origin.x)
        - (s1.origin.x - s2.origin.x) * (s2.end.y - s2.origin.y))
        / denominator ;

  float s = ((s1.origin.y - s2.origin.y) * (s1.end.x - s1.origin.x)
      - (s1.origin.x - s2.origin.x) * (s1.end.y - s1.origin.y))
      / denominator;

  result = Vecteur(s1.origin + r*(s1.end - s1.origin));
  return 0 <= r && r < 1 && 0 <= s && s < 1;
  }

  return false;
}

bool intersectBlock (const Segment & s, const Block & b) {
  Vecteur v(0, 0);
  Segment s1(b.leftBottom, b.leftBottom + Vecteur(0, b.height()));
  Segment s2(b.leftBottom, b.leftBottom + Vecteur(b.width(), 0));
  return intersectSegments(s, s1, v) || intersectSegments(s, s2, v);
}

int createMap(string & s) {
  stringstream ss(s);
  string tmp, sStreets, sAvenues;
  getline(ss, tmp, '(');
  getline(ss, sStreets, ')');
  getline(ss, tmp, '(');
  getline(ss, sAvenues, ')');

  vector<unsigned int> streets;
  vector<unsigned int> avenues;
  stringstream ssStreets(sStreets);
  stringstream ssAvenues(sAvenues);

  while (getline(ssStreets, tmp, ',')) {
      streets.push_back(atoi(tmp.c_str()));
  }

  while (getline(ssAvenues, tmp, ',')) {
      avenues.push_back(atoi(tmp.c_str()));
  }

  unsigned int counter = 0;
  Segment segment(Vecteur(streets[0], avenues[0]),
          Vecteur(streets[streets.size() - 1], avenues[avenues.size() - 1]));
  for (unsigned int i = 0; i < streets.size() - 1; ++i) {
    for (unsigned int j = 0; j < avenues.size() - 1; ++j) {
      Block block(Vecteur(streets[i], avenues[j]), Vecteur(streets[i+1], avenues[j+1]));
      if (intersectBlock(segment, block)) {
        counter++;
      }
    }
  }
  return counter;
}

int main(int argc, char * argv[]) {


  ifstream file;
  file.open(argv[1]);
  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      cout << createMap(line) << endl;
    }
    file.close();
  }
  return 0;
}
