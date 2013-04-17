#include <iostream>
using namespace std;

void f(int &x, int &y){
  x = 1;
  y = 2;
  x = y;
};


void g(int *x, int *y){
  *x = 1;
  *y = 2;
  x = y;
};

int main(int argc, char **argv){
  int a,b;
  f(a,b);
  cout << "f: " << a << " and " << b <<endl;

  int c, d;
  g(&c, &d);
  cout << "g: " << c << " and " << d <<endl;
};

