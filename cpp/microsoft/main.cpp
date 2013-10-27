#include <iostream>
#include "square.h"

using namespace std;

int main(int argc, char* argv[]) {
  Square * s = new Square(5);
  delete s;
  cout << "hello word" << endl;
  return 0;
}
