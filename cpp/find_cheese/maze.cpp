#include "maze.h"
#include <vector>

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


unsigned int oppositeDirection(unsigned int direction) {
  // direction - 1 -> to go back to 0,1,2,3 get the opposite with
  // direction + 2 % 4
  // direction + 1 go back to 1,2,3,4
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
 */
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

