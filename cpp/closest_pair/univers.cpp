#include "univers.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
Univers::Univers(){

}

void Univers::loadFromFile(char * path_name) {
  ifstream myfile (path_name);
  if (myfile.is_open()) {
    string line;
    if(myfile.good()) {
      unsigned int size;
      getline (myfile, line);
      stringstream size_streamed_line(line);
      size_streamed_line >> size;

      // set element for each value.
      for (unsigned int i = 0; i < size; i++) {
        getline(myfile, line);
        stringstream streamed_line(line);
        string token;

        int _x, _y;
        getline(streamed_line, token, ' ');
        istringstream my_x(token);
        my_x >> _x;
        getline(streamed_line, token, ' ');
        istringstream my_y(token);
        my_y >> _y;

        univers.push_back(new Point(_x, _y));

      }
    }
  }
  else {
    cout << "Unable to open file";
  }
  myfile.close();

};
