#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Accumulator {
    Accumulator() : counter(0) {};
    int counter;
    void operator()(int i) { counter += i; };
};

void print(int i) { std::cout << i << std::endl; }

int main(int argc, char * argv[]){

  std::vector<int> vec;
  for(int i = 0; i < 10; i++){
    vec.push_back(i);
  }

  // Using a functor
  Accumulator result  = std::for_each(vec.begin(), vec.end(), Accumulator());
  cout << "The sum is " << result.counter << endl;
  // Using a fonction pointer
  std::for_each(vec.begin(), vec.end(), print); // prints all elements

  return 0;
}
