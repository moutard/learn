#include "digit.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

bool isArmstrongNumber(string & number) {
  unsigned int n = number.size();
  unsigned int int_number = atoi(number.c_str());
  unsigned int sum = 0;
  for(unsigned int i = 0; i < n; ++i) {
    unsigned int digit = 0;
    char * c = new char(number[i]);
    //cout << *c << endl;
    // int atoi (const char * str);
    digit = atoi(c);
    sum += pow(digit, n);
  }

  return sum == int_number;
};
