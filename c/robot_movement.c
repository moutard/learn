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
  if (dir == UP && pos->x - 1 >= 0 && (back || grid[(pos->x - 1)* w + pos->y] <= 1)) {
      // if the case is empty 0 ! if the case is the final one 1.
      pos->x = pos->x - 1;
      return 1;
  }
  if (dir == DOWN && pos->x + 1 < h && (back || grid[(pos->x + 1) * w + pos->y] <= 1)) {
    pos->x = pos->x + 1;
    return 1;
  }
  if (dir == LEFT && pos->y - 1 >= 0 && (back || grid[pos->x * w + pos->y - 1] <= 1)) {
    pos->y = pos->y - 1;
    return 1;
  }
  if (dir == RIGHT && pos->y + 1 < w && (back || grid[pos->x * w + pos->y + 1] <= 1)) {
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

void printGrid (int * grid, int h, int w) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("%i ", grid[i*w + j]);
    }
    printf("\n");
  }
  printf("----------------\n");
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

  const int ALREADY_CROSSED = 3;
  const int FINAL_POSITION = 1;
  const int CURRENT_POSITION = 2;
  const int FREE_POSITION = 0;
  grid[0] = CURRENT_POSITION; // 2 position of the robot.
               // 3 is a position already crossed
  // grid[h*w -1] = FINAL_POSITION;// 1 final destination.

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
  int count = 0;
  while (last_index > 0) {
    count += 1;
    if (path[last_index] > 4) {
      // There is no direction that works you are in a dead end.
      printf("no more direction available for the cell dead end.\n");
      printf("pos: %i, %i\n", pos.x, pos.y);
      printPath(path, last_index + 1);
      printGrid(grid, h, w);

      path[last_index] = 6;
      last_index--;
      // Free the current cell and Go back to the previous cell.
      grid[pos.x*w + pos.y] = FREE_POSITION;
      move(grid, h, w, oppositeDirection(path[last_index]), &pos, 1);
      printf("after move back\n");
      printf("pos: %i, %i\n", pos.x, pos.y);
      printPath(path, last_index + 1);
      printGrid(grid, h, w);
      path[last_index] += 1;
    } else {
      // Try with the direction.
      if (move(grid, h, w, path[last_index], &pos, 0)) {
        printf("pos: %i, %i\n", pos.x, pos.y);
        grid[pos.x*w + pos.y] = CURRENT_POSITION;
        printPath(path, last_index + 1);
        printGrid(grid, h, w);
        // You just moved move to a good direction.
        // Check if it's the end is in the cell you just explored.
        if (pos.x*w + pos.y == h*w - 1) {
          // you found a good path.
          // - move back your position.
          // - change the last direction used.
          numberOfPath++;
          printf("good path found %i \n", numberOfPath);

          grid[pos.x*w + pos.y] = FREE_POSITION;
          int ok = move(grid, h, w, oppositeDirection(path[last_index]), &pos, 1);
          path[last_index] += 1;
          printf("after comming back\n");
          printf("pos: %i, %i\n", pos.x, pos.y);
          printPath(path, last_index + 1);
          printGrid(grid, h, w);

        } else {
          // you are on a new cell
          last_index++;
          path[last_index] = LEFT;
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


