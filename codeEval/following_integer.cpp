#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
void following_number (string xs) {
  bool ok = std::next_permutation(xs.begin(), xs.end());
  if (!ok) {
    size_t nzeros = xs.find_first_not_of('0');
    xs = xs.substr(nzeros);
    xs.insert(1, nzeros + 1, '0');
  }

    cout << xs << endl;
};

int main(int argc, char * argv[]) {

    string lineBuffer;
    ifstream file;
    file.open(argv[1]);

    while (!file.eof()) {
      getline(file, lineBuffer);
      if (lineBuffer.length() != 0) {
        following_number(lineBuffer);
      }
    }
};
