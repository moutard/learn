#ifndef GRID_H
#define GRID_H

#include <vector>
using namespace std;

/**
 * Square grid of int.
 */

class Grid {
  public:
    Grid();
    Grid(unsigned int size, int _default);
    ~Grid();
    unsigned int getSize();
    vector<vector<int> > get();
  private:
    unsigned int size;
    vector<vector<int> > grid;
};
#endif
