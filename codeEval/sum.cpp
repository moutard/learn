#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main (int argc, char * argv[]) {

  string sLineBuffer;
  ifstream file;
  file.open(argv[1]);

  unsigned int sum = 0;
  while(!file.eof()) {
    getline(file, sLineBuffer);
    if (sLineBuffer.length() != 0) {
      sum += (unsigned) atoi(sLineBuffer.c_str());
    }
  }
  cout << sum << endl;
};
