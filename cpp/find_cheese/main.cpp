#include <iostream>
#include "maze.h"
#include "grid_array.h"

using namespace std;

int main(int argc, char* argv[]) {
  // As interface do not exists in c++, to avoid abstract class that won't compile.
  Maze * maze = new Maze();
  FindCheese(maze);
  delete maze;
  return 0;
}
