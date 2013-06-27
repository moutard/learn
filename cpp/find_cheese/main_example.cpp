#include <iostream>
#include "grid_array.h"

using namespace std;

int main(int argc, char* argv[]) {
  // As interface do not exists in c++, to avoid abstract class that won't compile.
  ifstream myfile ("example_no_result.txt");
  if (myfile.is_open()) {
    GridArray * grid = new GridArray(myfile);
    grid->SetPosition(5, 1);
    cout << "grid array ok" << endl;
    FindCheese(grid);
    delete grid;
  }
  myfile.close();

  return 0;
}
