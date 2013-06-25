#include <iostream>
#include <fstream>
#include "digit.h"

using namespace std;

int main(int argc, char* argv[]) {
  string lineBuffer;

  ifstream file;
  file.open(argv[1]);
  while (!file.eof()) {
    getline(file, lineBuffer);
    if (lineBuffer.length() == 0)
        continue; //ignore all empty lines
    else {
      //do something here
      cout << getSum(lineBuffer) << endl;
    }
  }
  return 0;
}
