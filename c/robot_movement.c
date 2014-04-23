#include <stdlib.h>
#include <stdio.h>

typedef enum {
  LEFT = 1,
  DOWN = 2,
  RIGHT = 3,
  UP = 4
} Direction;

typedef struct {
  int x;
  int y;
} Position;

Direction oppositeDirection(Direction direction) {
  // direction - 1 -> translate in space {0,1,2,3}
  // direction + 2 % 4 -> get the opposite in the space {0,1,2,3}
  // direction + 1 -> translate to space {1,2,3,4}
  return ((direction + 1) % 4) + 1;
};

// Do ot move if you can not. (cell already visited.)
// if back remove the value of grid.
int move(int * grid, int h, int w, Direction dir, Position * pos, int back) {
  if (dir == UP && pos->x - 1 > 0 && grid[(pos->x - 1)* w + pos->y] <= 1) {
      // if the case is empty 0 ! if the case is the final one 1.
      pos->x = pos->x - 1;
      return 1;
  }
  if (dir == DOWN && pos->x + 1 < h && grid[(pos->x + 1) * w + pos->y] <= 1) {
    pos->x = pos->x + 1;
    return 1;
  }
  if (dir == LEFT && pos->y - 1 > 0 && grid[pos->x * w + pos->y - 1] <= 1) {
    pos->y = pos->y - 1;
    return 1;
  }
  if (dir == RIGHT && pos->y + 1 < w && grid[pos->x * w + pos->y + 1] <= 1) {
    pos->y = pos->y + 1;
    return 1;
  }
  return 0;
}


int stillPathToInspect(int pathLength, Direction dir) {
  return pathLength >  0 && dir <= 3;
}


void printPath (int * path, unsigned int length) {
  for (unsigned int i = 0; i < length; i++) {
    printf("%i ", path[i]);
  }
  printf("\n");
}
int main(int argc, char *argv[]) {
  unsigned int numberOfPath = 0;
  const unsigned int h = 4;
  const unsigned int w = 4;

  // Represent the grid that the robot can walk.
  unsigned int grid[h*w];

  // path of the robot (contains the direction that the robot took from the
  // top-left cell)
  // the max length is h*w go through all the cell.
  // Should be work as a queue.
  unsigned int pathLength = 0;
  unsigned int path[h*w];

  for (unsigned int i = 0; i < h; i++) {
    for (unsigned int j = 0; j < w; j++) {
      grid[i*w + j] = 0;
      path[i*w + j] = 6;
    }
  }

  grid[0] = 2; // 2 position of the robot.
               // 3 is a position already crossed
  grid[h*w -1] = 1;// 1 final destination.

  // Current position of the robot.
  Position pos;
  pos.x = 0;
  pos.y = 0;
  Direction dir = LEFT;

  // the first cell is never used. (not a bif deal it corresponds to the
  // starting point)
  int last_index = 1;
  path[last_index] = dir;

  // Until there is a cell to visit.
  while (last_index > 0) {
    if (path[last_index] > 4) {
      // There is no direction that works you are in a dead end.
      printf("no more direction available for the cell - dead end move back\n");
      path[last_index] = 6;
      last_index--;
      // Go back to the previous cell.
      move(grid, h, w, oppositeDirection(path[last_index]), &pos);
      grid[pos.x*w + pos.y] = 0;
    } else {
      // Try with the direction.
      printPath(path, last_index + 1);
      if (move(grid, h, w, path[last_index], &pos)) {
        // You just moved move to a good direction.
        last_index++;
        path[last_index] = 0;
        // Check if the cheese is in the cell you just explored.
        if (grid[pos.x*w + pos.y] == 1) {
          printf("good path found\n");
          numberOfPath++;
          last_index--;
          // can not move because we already went there.
          int ok=move(grid, h, w, oppositeDirection(path[last_index]), &pos);
          printf("ok\n: %i", ok);
          path[last_index] += 1;
        } else {
          grid[pos.x*w + pos.y] = 2;
        }
      } else {
        // The next direction to analyse.
        path[last_index] += 1;
      }
    }
  }
  printf("number of path: %i\n" , numberOfPath);
  return 0;
}


