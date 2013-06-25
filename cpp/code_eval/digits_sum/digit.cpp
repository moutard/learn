#include "digit.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

unsigned int getSum(string & number) {
  unsigned int sum = 0;
  for(unsigned int i = 0; i < number.size(); ++i) {
    unsigned int digit = 0;
    char * c = new char(number[i]);
    //cout << *c << endl;
    // int atoi (const char * str);
    digit = atoi(c);
    sum += digit;
  }

  return sum;
};
