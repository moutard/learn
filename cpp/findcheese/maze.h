#include <iostream>

#ifndef MAZE_H
#define MAZE_H

using namespace std;

enum Direction {

 left = 1, // move left (x-1)

 down = 2, // move down (y-1)

 right = 3, // move right (x+1)

 up = 4  // move up (y+1)

};

// Should be abstract class.
class Maze {
  public:

  Maze();
  virtual ~Maze();
       // Will create a session and a maze.  The maze will be no larger than 100 by 100 units in size.  The mouse and a piece of cheese will be positioned at random locations within the maze.

  void Initialize();

       // Will attempt to move the mouse in one direction.  If the move was successful, returns true.  If there was a wall and the move failed, returns false.

  bool Move(Direction tryMovingMouseInThisDirection);
  bool Move(unsigned int tryMovingMouseInThisDirection);

       // Will return true if the mouse and cheese are at the same location, false otherwise.

  bool Success();

};

inline unsigned int oppositeDirection(unsigned int direction);
void FindCheese(Maze * maze);
#endif
