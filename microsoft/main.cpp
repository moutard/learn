#include <iostream>
#include "shape.h"
#include "square.h"

int main(int argc, char* argv[]) {
  Square * s = new Square(5);
  delete s;
  return 0;
}
