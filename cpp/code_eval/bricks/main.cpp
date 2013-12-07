#include <iostream>
#include <fstream>
#include <sstream>      // std::istringstream
#include <string>
#include <vector>
#include "wall.h"

using namespace std;

/**
 * Given an vector
 * print "-" if no solution
 * print ids 1,2,3
 * make sure that there is no trailing coma.
 */
void writeSolution (const vector<double> & solution) {
  if (solution.size() == 0) {
    cout << "-";
  } else {
    unsigned int i;
    for (i = 0; i < solution.size() - 1; ++i) {
      cout << solution[i] << ",";
    }
    cout << solution[i];
  }
  cout << endl;
}

/**
 *  @param string: s pattern that represents a wall.
 *  Parse this to find value of opposite vertices.
 *  [-1,-5] [5,-2]
 */
Wall * createWall(const string & s) {
  double a, b, u, v;
  string tmp;

  std::stringstream ss(s);

  getline(ss, tmp, '[');
  getline(ss, tmp, ',');
  a = (double)atof(tmp.c_str());
  getline(ss, tmp, ']');
  b = (double)atof(tmp.c_str());
  getline(ss, tmp, '[');
  getline(ss, tmp, ',');
  u = (double)atof(tmp.c_str());
  getline(ss, tmp, ']');
  v = (double)atof(tmp.c_str());

  return new Wall(a, b, u, v);
}

void readBrickCoordinates(const string & s, vector<double> & ve) {
  stringstream ss(s);
  double a, b, c, u, v, w, id;
  string tmp;
  getline(ss, tmp, '(');
  getline(ss, tmp, ' ');
  id = (double)atof(tmp.c_str());
  getline(ss, tmp, '[');
  getline(ss, tmp, ',');

  a = (double)atof(tmp.c_str());
  getline(ss, tmp, ',');
  b = (double)atof(tmp.c_str());
  getline(ss, tmp, ']');
  c = (double)atof(tmp.c_str());
  getline(ss, tmp, '[');
  getline(ss, tmp, ',');
  u = (double)atof(tmp.c_str());
  getline(ss, tmp, ',');
  v = (double)atof(tmp.c_str());
  getline(ss, tmp, ']');
  w = (double)atof(tmp.c_str());

  ve[0] = id;
  ve[1] = a;
  ve[2] = b;
  ve[3] = c;
  ve[4] = u;
  ve[5] = v;
  ve[6] = w;

}

void readLine(const string & sLineBuffer) {
  // A line looks like the following example:
  // [-1,-5] [5,-2]|(1 [4,7,8] [2,9,0]);(2 [0,7,1] [5,9,8])
  stringstream ssLineBuffer(sLineBuffer);
  string wall;
  vector<double> v(7);
  vector<double> solution;
  char delim_bar = '|';
  getline(ssLineBuffer, wall, delim_bar);
  Wall * w = createWall(wall);
  string brick;
  char delim_coma = ';';
  while (std::getline(ssLineBuffer, brick, delim_coma)) {
    readBrickCoordinates(brick, v);
    if (w->fitHole(v[1], v[2], v[3], v[4], v[5], v[6])) {
      solution.push_back(v[0]);
    }
  }
  writeSolution (solution);
  solution.clear();
  delete w;
}

int main(int argc, char* argv[]) {
  string sLineBuffer;

  ifstream file;
  file.open(argv[1]);
  while (!file.eof()) {
    std::getline(file, sLineBuffer);
    if (sLineBuffer.length() == 0)
        continue; //ignore all empty lines
    else {
      stringstream isLineBuffer(sLineBuffer);
      readLine(sLineBuffer);
    }
  }
  return 0;
}
