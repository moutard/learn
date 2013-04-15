#include <string>
#include <vector>
#include <iostream>
#include <sstream>      // std::istringstream
#include <stdlib.h>     /* atoi abs*/
using namespace std;
/**
 * split a line at the space position.
 */
bool parseLineInVector(string s, vector<int> & v){

  istringstream ss( s );
  while (!ss.eof()) {
    string x;               // here's a nice, empty string
    getline( ss, x, ' ' );  // try to read the next field into it

    if(x != "" && x != " "){
      int value = atoi(x.c_str());
      v.push_back(value);
    }
    cout << x << endl;      // print it out, even if we already hit EOF
  }
  return true;
}

bool isJollyJumper(const vector<int> & v) {
  // Problem if v.size() is very big.
  vector<int> difference(v.size() + 1, 0);
  difference[0] = 1;
  for(int i = 0; i < v.size(); ++i){
    difference[abs(v[i] - v[i+1])] += 1;
  }
  for(vector<int>::iterator it = difference.begin(); it < v.end(); ++it){
    if(*it != 1){
      return false;
    }
  }
  return true;
}

/**
 A sequence of n > 0 integers is called a jolly jumper if the absolute values of the differences between successive elements take on all possible values 1 through n - 1. eg.

1 4 2 3
is a jolly jumper, because the absolute differences are 3, 2, and 1, respectively. The definition implies that any sequence of a single integer is a jolly jumper. Write a program to determine whether each of a number of sequences is a jolly jumper.
Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file is one test case. Each test case will contain an integer n < 3000 followed by n integers representing the sequence. The integers are space delimited.

Output sample:

For each line of input generate a line of output saying 'Jolly' or 'Not jolly'.
*/
