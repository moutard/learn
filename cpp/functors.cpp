#include <iostream>
#include <iterator>
#include <algorithm>

class CountFrom {
private:
  int &count;
public:
  CountFrom(int &n) : count(n) {}
  int operator()() { return count++; }
};

int main() {
  int state(10);
  std::generate_n(std::ostream_iterator<int>(std::cout, "\n"), 11, CountFrom(state));
  return 0;
}
