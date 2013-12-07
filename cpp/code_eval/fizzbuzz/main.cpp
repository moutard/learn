#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>     /* atoi */

using namespace std;

void fizzbuzz(unsigned int a, unsigned int b, unsigned int N) {
  for (unsigned int i = 1; i <= N; ++i) {
    bool isDivisibleByA = ((i % a) == 0);
    bool isDivisibleByB = ((i % b) == 0);
    if (isDivisibleByA || isDivisibleByB) {
      if (isDivisibleByA) {cout << "F";}
      if (isDivisibleByB) {cout << "B";}
    } else {
      cout << i;
    }
    if (i < N) cout << " ";
  }
  cout << endl;
};

void fizzbuzzNoModulo(unsigned int a, unsigned int b, unsigned int N) {
  int fizz = a;
  int buzz = b;
  string outp;
  for(int i = 1; i < = N; ++i) {
    fizz--;
    buzz--;
      if (fizz == 0 && buzz == 0) {
        outp = "FizzBuzz";
        fizz = 3;
        buzz = 5;
      } else if (fizz == 0) {
        outp = "Fizz";
        fizz = 3;
      } else if (buzz == 0) {
      outp = "Buzz";
      buzz = 5;
    } else {
      outp = i.ToString();
    }
    result += outp + ", ";
  }
};

int main(int argc, char* argv[]) {

  string lineBuffer;

  ifstream file;
  file.open(argv[1]);
  while (!file.eof()) {
    getline(file, lineBuffer);
    if (lineBuffer.length() == 0)
        continue; //ignore all empty lines
    else {
      string tmp;
      unsigned int a, b, N;
      stringstream iss(lineBuffer);
      getline(iss, tmp, ' ');
      a = (unsigned int) atoi(tmp.c_str());
      getline(iss, tmp, ' ');
      b = (unsigned int) atoi(tmp.c_str());
      getline(iss, tmp, ' ');
      N = (unsigned int) atoi(tmp.c_str());
      //do something here
      fizzbuzz(a, b, N);
    }
  }
  return 0;
}
