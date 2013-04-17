#include <iostream>
#include <vector>

using namespace std;

class Tree {
  public:
    int value;
    Tree * left;
    Tree * right;

    Tree(int _value) : left(NULL), right(NULL), value(_value){}

    void insert(int i){
      if(i < value){
        if(left == NULL){
          left = new Tree(i);
        } else {
          left->insert(i);
        }
      } else {
        if(right == NULL){
          right = new Tree(i);
        } else {
          right->insert(i);
        }
      }
    };

    void preOrder(){
      if(right == NULL && left == NULL){
        cout << value << endl;
      } else if(left != NULL){
        left->preOrder();
        cout << value << endl;
        right->preOrder();
      } else {
        cout << value << endl;
        right->preOrder();
      }

    };
};

Tree * constructBinarySearchTree(const vector<int> & v ){
  Tree * t = new Tree(v[0]);
  for(unsigned int i = 1; i < v.size(); i++){
    t->insert(v[i]);
  }
  return t;
};

int main(int argc, char **argv){
  vector<int>  v(5, 0);
  v[0] = 6;
  v[1] = 4;
  v[2] = 10;
  v[3] = 3;
  v[4] = 5;

  Tree * t = constructBinarySearchTree(v);
  t->preOrder();
  return 0;
};

