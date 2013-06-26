#include <iostream>
#include <fstream>
#include "digit.h"
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Pairs {
  public:
    Pairs();
    ~Pairs();
    void pairsFromLine(string & line);
    bool dichotomiqueFind();
    void findAllPairs();
    void print();
    unsigned int next_non_equal();
  private:
    unsigned int sum;
    unsigned int min_index, max_index;
    vector<unsigned int> list;
    vector<unsigned int> pairs;
};

Pairs::Pairs() {};
Pairs::~Pairs() {};
void Pairs::print() {
  if(pairs.size() == 0) {
    cout << "NULL" << endl;
  } else {
    for(unsigned int i = 0; i < pairs.size(); i+=2) {
      cout << pairs[i] << "," << pairs[i+1];
      if(i <  pairs.size() - 2) {
        cout << ";";
      }
    }
    cout << endl;
  }
};

void Pairs::pairsFromLine(string & line) {
  istringstream ss_line(line);
  string _list;
  string _sum;
  getline(ss_line, _list, ';');
  getline(ss_line, _sum, ';');
  sum = atoi(_sum.c_str());
  string number;

  istringstream ss_list(_list);

  while ( std::getline( ss_list, number, ',' ) ) {
    //cout << atoi(number.c_str()) << ' ';
    list.push_back(atoi(number.c_str()));
  }
  //cout << ";" << sum << endl;
  min_index = 0;
  max_index = list.size() - 1;
};

bool Pairs::dichotomiqueFind() {
  unsigned int _max_index = max_index;
  unsigned int _min_index = min_index + 1;
  unsigned int _current_index;
  bool hasResult = false;

  while(_max_index >= _min_index) {
    _current_index = (_max_index - _min_index) / 2 + _min_index;
    unsigned int _sum = list[_current_index] + list[min_index];
    if(_sum == sum) {
      // we have found a pair.
      // FIXME: problem with the trainling coma.
      //cout << list[min_index] << "," << list[_current_index];
      // we can stop are we are looking for unique pairs.
      pairs.push_back(list[min_index]);
      pairs.push_back(list[_current_index]);
      _max_index = _min_index - 1; // to be sure to stop the loop.
      hasResult = true;
    } else if(_sum > sum) {
      _max_index = _current_index - 1;
    } else {
      _min_index = _current_index + 1;
    }
  }

  min_index = next_non_equal();
  max_index = _current_index;
  return hasResult;
};

unsigned int Pairs::next_non_equal() {
  while(min_index < list.size() - 1 && list[min_index] == list[min_index + 1]) {
    min_index +=1;
  }
  return min_index + 1;
};

void Pairs::findAllPairs(){
  while(max_index > min_index) {
    dichotomiqueFind();
  }
  print();
};

int main(int argc, char* argv[]) {
  string lineBuffer;

  ifstream file;
  file.open(argv[1]);
  while (!file.eof()) {
    getline(file, lineBuffer);
    if (lineBuffer.length() == 0)
        continue; //ignore all empty lines
    else {
      //do something here
      Pairs * p = new Pairs();
      p->pairsFromLine(lineBuffer);
      p->findAllPairs();
      delete p;
    }
  }
  return 0;
}
