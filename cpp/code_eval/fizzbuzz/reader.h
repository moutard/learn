#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Reader {

public:
  Reader(char * sPathToFile);
  bool getNewInstance(std::vector<unsigned int> & v);

private:
  void readLine(const std::string & s, std::vector<unsigned int> & v);
  std::ifstream _ifFile;

};
