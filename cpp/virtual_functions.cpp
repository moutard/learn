#include <iostream>
using namespace std;

class A{
  public:
    void virtual Info(){cout<<"Info A"<<endl;};
    void About(){cout<<"About A"<<endl;};
};

class A1 : public A {
  public:
    void virtual Info(){cout<<"Info A1"<<endl;};
    void About(){cout<<"About A1"<<endl;};
};

class A2 : public A {
  public:
    void virtual Info(){cout<<"Info A2"<<endl;};
    void About(){cout<<"About A2"<<endl;};
};

int main(int argc, char **argv){
  A *a1, *a2;
  a1 = new A1();
  a2 = new A2();
  a2->Info();
  a2->About();
  A *b = (A*) a1; // dynamic_cast
  b->Info();

  A * base;
  A1 * derivated = new A1();
  base = dynamic_cast<A*>(derivated); //OK - derivated to base.
  // WRONG - derivated = dynamic_cast<A1*>(base);
  base->Info();
  return 0;
};

