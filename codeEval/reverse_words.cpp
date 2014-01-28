#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Given a string and the startIndex and the endIndex
 * swap each elements in the words in the range [startIndex, endIndex]
 */
void reverse (string & sLine, unsigned int startIndex, unsigned int endIndex) {
  unsigned int length = endIndex - startIndex;
  unsigned int middle = length / 2;

  for (unsigned int i = 0; i <= middle; ++i) {
    std::swap(sLine[i + startIndex], sLine[endIndex - i]);
  }

};

/**
 * first reverse the whole line.
 * Then reverse each word (find a word between 2 space)
 */
void reverseWords (string & sLine) {
  reverse(sLine, 0, sLine.length() - 1);

  unsigned int start = 0;
  std::size_t found = sLine.find(" ");
  while(found!=std::string::npos) {
    // To avoid problem if 2 consecutives space.
    // Rq: the number of space is conserved.
    if (found > start) {
      reverse(sLine, start, found -1);
    }
    start = found + 1;
    found = sLine.find(" ", found + 1);
  }
  if (start < sLine.length() - 1) {
    // TO avoid problem with trailing white space.
    reverse(sLine, start, sLine.length() - 1);
  }
  cout << sLine << endl;
};

int main (int argc, char * argv[]) {

  string sLineBuffer;
  ifstream file;
  file.open(argv[1]);

  while(!file.eof()) {
    getline(file, sLineBuffer);
    if (sLineBuffer.length() != 0) {
      reverseWords(sLineBuffer);
    }
  }
};
