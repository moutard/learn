#include <iostream>
#include <fstream>
#include <string>
#include "wall.h"

using namespace std;

int main(int argc, char* argv[]) {
  string stringLineBuffer;

  ifstream file;
  file.open(argv[1]);
  while (!file.eof()) {
    getline(file, stringLineBuffer);
    if (stringLineBuffer.length() == 0)
        continue; //ignore all empty lines
    else {
      cout << "True" << endl;
    }
  }
  return 0;
}
