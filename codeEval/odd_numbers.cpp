#include <iostream>

void printOddNumbers(unsigned int N) {
  unsigned int median = N/2;
  for (unsigned int i = 0; i <= median; ++i) {
    std::cout << 2*i + 1 << std::endl;
  }
}

int main(int argc, char * argv[]) {
  printOddNumbers(99);
  return 0;
}
