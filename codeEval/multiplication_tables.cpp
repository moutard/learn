#include <iostream>
#include <string>
#include <sstream>

std::string formatNumber(unsigned int i) {
  std::stringstream ss;
  ss << i;
  std::string s(ss.str());
  std::string result(4, ' ');
  for (unsigned int i = 0; i < s.length(); ++i) {
    result[4 - 1 - i] = s[s.length() - 1 - i];
  }
  return result;
}

void multiplicationTable() {
  for (unsigned int i = 1; i <= 12; i++) {
    for (unsigned int j = 1; j <= 12; ++j) {
      std::cout << formatNumber(i*j);
    }
    std::cout << std::endl;
  }
}
int main(int argc, char * argv[]) {
  multiplicationTable();
  return 0;
}
