#include <iostream>
#include <iterator>
#include <algorithm>

// functor is pretty much just a class which defines the operator(). That lets
// you create objects which "look like" a function.
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
