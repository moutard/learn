#include "reader.h"
#include <sstream>
#include <stdlib.h>     /* atoi */

using namespace std;

Reader::Reader(char * sPathToFile) {
  _ifFile.open(sPathToFile);
}

void Reader::readLine(const std::string & lineBuffer, std::vector<unsigned int> & v) {
  istringstream issLine(lineBuffer);
  string sValue;
  while (getline(issLine, sValue, ' ')) {
    unsigned int iValue = (unsigned int)atoi(sValue.c_str());
    v.push_back(iValue);
  }
}

bool Reader::getNewInstance(vector<unsigned int> & v) {
  bool bHasFound = false;
  string lineBuffer;
  while (!_ifFile.eof()) {
    getline(_ifFile, lineBuffer);
    if (lineBuffer.size() != 0) {
       bHasFound = true;
       break;
    }
  }

  if (bHasFound) {
    readLine(lineBuffer, v);
  }
  return bHasFound;
}
