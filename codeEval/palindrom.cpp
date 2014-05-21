#include <string>
#include <iostream>

bool isPalindrom(const std::string & s) {
  unsigned int median = s.length() / 2;
  bool isPalindrom = true;
  for (unsigned int i = 0; i <= median; ++i) {
    isPalindrom = isPalindrom && s[i] == s[s.length() - 1 - i];
  }
  return isPalindrom;
}

int main(int argc, char * argv[]) {
  std::string s(argv[1]);
  std::cout << isPalindrom(s) << std::endl;
  return 0;
}
