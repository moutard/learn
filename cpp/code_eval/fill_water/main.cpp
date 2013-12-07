#include <iostream>
#include <fstream>
#include <vector>
#include "reader.h"

using namespace std;

int volume(const std::vector<unsigned int> & v) {
  // auto iMax = std::max_element(v.begin(), v.end());
  unsigned int iMaxIndex = 0;
  unsigned int iMaxValue = 0;
  unsigned int volume = 0;

  // Find the max value and the corresponding index.
  for (unsigned int i = 0; i < v.size(); ++i) {
    if (v[i] > iMaxValue) {
      iMaxIndex = i;
      iMaxValue = v[i];
    }
  }

  unsigned int currentMax = 0;
  for (unsigned int i = 0; i < iMaxIndex; ++i) {
    if (currentMax > v[i]) {
      volume += currentMax - v[i];
    }
    // Update the currentMax.
    currentMax = std::max(currentMax, v[i]);
  }

  currentMax = 0;
  for (unsigned int i = v.size() - 1; i > iMaxIndex; --i) {
    if (currentMax > v[i]) {
      volume += currentMax - v[i];
    }
    // Update the currentMax.
    currentMax = std::max(currentMax, v[i]);
  }

  return volume;
}

int svolume(const std::vector<unsigned int> & v) {

  vector<unsigned int>::const_iterator left = v.begin();
  vector<unsigned int>::const_iterator right = v.end();

  unsigned int maxLeft = *left;
  unsigned int maxRight = *right;

  int volume = 0;

  while(left != right) {
    if (maxLeft < maxRight) {
      volume += *left;
      ++left;
    } else {
      volume += *right;
      --right;
    }
  }

  return volume;
}

void print_v(const vector<unsigned int> & v) {
  cout << "print_v" << endl;
  for (vector<unsigned int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {

  Reader r(argv[1]);

  //
  std::vector<unsigned int> v;
  while(r.getNewInstance(v)) {
    print_v(v);
    cout << volume(v) << endl;
    cout << svolume(v) << endl;
    v.clear();
  }
  return 0;
}
