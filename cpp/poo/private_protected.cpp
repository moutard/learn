#include <iostream>
using namespace std;

class Base {
  private:
    int _private;
  protected:
    int _protected;
  public:
  int getProtected(){ return _protected;};
};

class Derivated : public Base {
  private:
    int y;
  public:
    //int getPrivate(){return _private;} // Error ! can't access private form a derivated class.
    void setProtected(int i){_protected = i;} // protected is accessible by the derivated class inside the class.
};

int main(int agrc, char **argv){
  Base * a = new Base();
  Derivated * b = new Derivated();

  // a->_protected; // error you can't access a protected variable outside the class
  a->getProtected(); // OK uses public access function
  b->setProtected(3); // OK uses public access function.
  cout << b->getProtected() << endl;
  delete a;
  delete b;
  return 0;
};
