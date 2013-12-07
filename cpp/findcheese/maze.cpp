#include "maze.h"
#include <vector>
#include <iostream>

using namespace std;

Maze::Maze(){};
Maze::~Maze(){};

void Maze::Initialize(){

};

bool Maze::Move(Direction tryMovingMouseInThisDirection){
  return false;
};

bool Maze::Move(unsigned int tryMovingMouseInThisDirection){
  return false;
};

bool Maze::Success(){
  return false;
};

/**
 * Given a direction as an unsigned int, return the opposite one.
 * i.e. if you take this direction you go back to the previous cell.
 * 1 <-> 3
 * 2 <-> 4
 */
unsigned int oppositeDirection(unsigned int direction) {
  // direction - 1 -> translate in space {0,1,2,3}
  // direction + 2 % 4 -> get the opposite in the space {0,1,2,3}
  // direction + 1 -> translate to space {1,2,3,4}
  return ((direction + 1) % 4) + 1;
};

/**
 * The mouse is at a random cell.
 * 1) Try to move using direction x in the order given by enum (left, down, right, up).
 *   we note -x the opposite direction, the direction that allows you to go back
 *   to the previous cell.
 *  if there is a direction x that works that is not the opposite direction of
 *  the previous cell then
 *   - push back x in the vector.
 *   - go back to (1)
 *  if there is no direction that works except the opposite direction, you are
 *  in a dead end. do go back to the previous cell using the opposite direction
 *  and use the next direction.
 *
 *  if you go back to the initial position and there is no direction remaining
 *  then stop the loop there is no solution to the maze. You can't find the
 *  cheese.
 *
 *  Analysis: if the maze is a grid of size N*N.
 *  - Space complexity: O(N*N) in worst case you visit all the cells before finding
 *  the cheese, the vector path has a length N^2
 *  - Time complexity: looks like graph traversal. Each vertex is a cell,
 *  if there two neighbors cells that have no wall between, there is a edge
 *  between two corresponding vertices. O(V^2) visiting all the cells.
 */
void FindCheese(Maze * maze) {
  // Vector that stores the path of the mouse.
  // Each element of the vector corresponds to a visited cell. the ith element
  // is the ith cell visited in the order of the path, and it contains the
  // direction that allow to go to the next cell.
  vector<unsigned int> path;

  // The initial cell.
  path.push_back(0);

  // While there is cell to visit.
  while (path.size() > 0) {
    unsigned int last_index = path.size() - 1;

    if (path[last_index] > 4) {
      // There is no direction that works you are in a dead end.
      path.pop_back();
      // Go back to the previous cell.
      maze->Move(oppositeDirection(path.back()));
    } else {
      // There is still direction you can try.
      path[last_index] += 1;
      if((last_index >= 1) // There is a cell before.
          && (path[last_index] == oppositeDirection(path[last_index -1])) // This cell is not the opposite one
        ) {
        // The direction you want to try go back to the previous cell you
        // already visited, so don't try it.
        path[last_index] += 1;
      }
      if (maze->Move(path.back())) {
        // You move to a good direction.
        cout << path.back() << endl;
        path.push_back(0);

        // Check if the cheese is in the cell you just explored.
        if (maze->Success()) {
          // Print path, consecutive direction you have to take from the
          // first cell to reach the cheese.
          for(unsigned int i = 0; i < path.size(); ++i ) {
            cout << path[i] << " ";
          }
          cout << endl;
          cout << "Success" << endl;
          return;
        }

      } else {
        // There is a wall in the direction you tried.
        // You will try another direction if needed in the next while loop.
      }
    }
  }

  cout << "This maze has no solution" << endl;
};

