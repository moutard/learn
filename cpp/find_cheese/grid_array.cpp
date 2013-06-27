#include "grid_array.h"
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include <algorithm>    // std::min
using namespace std;

GridArray::GridArray(){
  size = 0;
};
/**
 * create an grid of size n*n fill with value 0.
 */
GridArray::GridArray(unsigned int _size, int _default /*= 0*/) {
  size = _size;
  grid = new int*[size];
  for (unsigned int i = 0; i < size; ++i) {
    grid[i] = new int[size];
    for(unsigned int j = 0; j < size; ++j) {
      grid[i][j] = _default;
    }
  }
};

GridArray::GridArray(ifstream & _input_file) {
  int x = 0, y = 0;
  string line;
  if(_input_file.good()) {
    getline (_input_file, line);
    stringstream size_streamed_line(line);
    size_streamed_line >> size;
    cout << "Initialize grid with size : " << size << endl;
    // initialise the grid with default value.
    grid = new int*[size];
    for (unsigned int i = 0; i < size; ++i) {
      grid[i] = new int[size];
      for(unsigned int j = 0; j < size; ++j) {
        grid[i][j] = 0;
      }
    }
    // set element for each value.
    while (getline(_input_file, line)) {
      stringstream streamed_line(line);
      string token;
      int value;
      while(getline(streamed_line, token, ' ')) {
        istringstream my_value(token);
        my_value >> value;
        grid[x][y] = value;
        y++;
      }
      y = 0;
      x++;
    }
  }
  cout << "grid initalized" << endl;
  print();
};

GridArray::~GridArray() {
  for(unsigned int i = 0; i < size; ++i) {
    delete[] grid[i];
  }
  delete[] grid;
};

unsigned int GridArray::getSize() {
  return size;
};

int GridArray::getElement(unsigned int x, unsigned int y) {
  if(x < size && y < size && x >= 0 && y >= 0) {
    return grid[x][y];
  } else {
    return INT_MAX;
  }
};

void GridArray::setElement(unsigned int x, unsigned int y, int _value) {
  grid[x][y] = _value;
};

void GridArray::print(){
  for (unsigned int i = 0; i < size; ++i) {
    for(unsigned int j = 0; j < size; ++j) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
};

int GridArray::findShortestPath() {

  // handle the first line differently to performance issue, avoid a if in the
  // loop that should be true only once.
  for (unsigned int j = 1; j < size; ++j) {
    grid[0][j] += grid[0][j-1];
  }

  for (unsigned int i = 1; i < size; ++i) {
    for (unsigned int j = 0; j < size; ++j) {
      grid[i][j] += min(getElement(i - 1, j), getElement(i, j - 1));
    }
  }
  print();
  return grid[size - 1][size - 1];
};

void GridArray::SetPosition(unsigned int _x, unsigned int _y) {
  x = _x;
  y = _y;
};

bool GridArray::Move(unsigned int direction) {
  if (direction == 1) { // LEFT
    if (grid[x][y - 1] > 0) {
      y -= 1;
      return true;
    };
    return false;
  } else if (direction == 2) { // DOWN
    if (grid[x + 1][y] > 0) {
      x += 1;
      return true;
    }
    return false;
  } else if(direction == 3) { // RIGHT
    if (grid[x][y + 1] > 0) {
      y += 1;
      return true;
    }
    return false;
  } else if(direction == 4) { // UP

    if(grid[x - 1][y] > 0) {
      x -= 1;
      return true;
    }
    return false;
  } else {
    return false;
  }
};

bool GridArray::Success() {
  return grid[x][y] == 3;
};

unsigned int oppositeDirection(unsigned int direction) {
  // direction - 1 -> to go back to 0,1,2,3 get the opposite with
  // direction + 2 % 4
  // direction + 1 go back to 1,2,3,4
  return ((direction + 1) % 4) + 1;
};

void FindCheese(GridArray * maze) {
  // Vector that stores the path of the mouse.
  // Each element of the vector corresponds to a visited cell. the ith element
  // is the ith cell visited in the order of the path, and it contains the
  // direction that allow to go to the next cell.
  vector<unsigned int> path;

  // the initial cell.
  path.push_back(0);

  // while there is cell to visit.
  while (path.size() > 0) {
    unsigned int last_index = path.size() - 1;

    if (path[last_index] > 4) {
      // There is no direction that works you are in a dead end.
      path.pop_back();
      // go back to the previous cell.
      maze->Move(oppositeDirection(path.back()));
    } else {
      // there is still direction you can try.
      path[last_index] += 1;
      if((last_index >= 1) // There is a cell before.
          && (path[last_index] == oppositeDirection(path[last_index -1])) // this cell is not the opposite one

        ) {
        // the direction you want to try go back to the previous cell you
        // already visited, so don't try it.
        path[last_index] += 1;
      }
      if (maze->Move(path.back())) {
        // you move to a good direction.
        cout << path.back() << endl;
        path.push_back(0);

        // Check if the cheese is in the cell you just explored.
        if (maze->Success()) {
          // print path:
          for(unsigned int i = 0; i < path.size(); ++i ) {
            cout << path[i] << " ";
          }
          cout << endl;
          cout << "Success" << endl;
          return;
        }

      } else {
        // there is a wall in the direction you tried.
        // try another direction.
      }
    }
  }

  cout << "This maze has no solution" << endl;
};

