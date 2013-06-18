#include <iostream>
#include <vector>
#include "point.h"

#ifndef UNIVERS_H
#define UNIVERS_H

using namespace std;

class Univers {
  public:
    Univers();
    void loadFromFile(char * path_name);
  private:
    vector<Point* > univers;
};

#endif // UNIVERS_H
