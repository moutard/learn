#include <string>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>      // std::istringstream
#include <stdlib.h>     /* atoi */
using namespace std;

int distance(int Ax, int Ay, int Bx, int By) {
  return sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By));
};

void readLine (const string & line) {
  int ax, ay, bx, by;
  string tmp;
  std::stringstream ss(line);
  getline(ss, tmp, '(');
  getline(ss, tmp, ',');
  ax = (int)atoi(tmp.c_str());
  getline(ss, tmp, ')');
  ay = (int)atoi(tmp.c_str());
  getline(ss, tmp, '(');
  getline(ss, tmp, ',');
  bx = (int)atoi(tmp.c_str());
  getline(ss, tmp, ')');
  by = (int)atoi(tmp.c_str());
  cout << distance(ax, ay, bx, by) << endl;
};

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
