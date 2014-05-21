#include <string>
#include <vector>
#include <map>
#include <algorithm>    // std::sort
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

unsigned int min(unsigned int a, unsigned int b, unsigned int c) {
  unsigned int min;
  if (a < b) {
    min = a;
  } else {
    min = b;
  }

  if (c < min) {
    return c;
  } else {
    return min;
  }
};

int levenshteinDistance(const std::string & s, const std::string & t) {

  // Degenerate Cases.
  if (s.compare(t)==0) { return 0;}
  unsigned int iSLength = s.size();
  unsigned int iTLength = t.size();
  if (iSLength == 0) {return iTLength;}
  if (iTLength == 0) {return iSLength;}

  // Create the two vectors (corresponds to the previous and current line of the matrix)
  unsigned int v0[iTLength + 1];
  unsigned int v1[iTLength + 1];

  // Initialize each vector.
  for (unsigned int i = 0; i < iTLength + 1; ++i) {
    v0[i] = i;
  }

  for (unsigned int i = 0; i < iSLength; ++i) {
    // Calculate v1 (the current row distance)
    v1[0] = i + 1;

    // Use the formulat to fill in the rest of the row.
    for (unsigned int j = 0; j < iTLength; ++j) {
      unsigned int cost = (s[i] == t[j]) ? 0 : 1;
      v1[j+1] = min(v1[j] + 1, v0[j+1] + 1, v0[j] + cost);
    }

    // copy v1 (current row) to v0;
    for (unsigned int k = 0; k < iTLength + 1; ++k) {
      v0[k] = v1[k];
    }
  }
  return v1[iTLength];
};

unsigned int search(std::string segment, std::string dna, int max_distance) {

  std::map<int, std::vector<std::string> > seq;
  unsigned int counter = 0;
  unsigned int segmentLength = segment.size();
  unsigned int dnaLength = dna.size();
  std::string substring;

  for (unsigned int i = 0; i < (dnaLength - segmentLength + 1); ++i) {
    substring = dna.substr(i, segmentLength);
    int lev = levenshteinDistance(segment, substring);
    if (lev <= max_distance) {
      counter++;
      seq[lev].push_back(substring);
    }
  }
  std::map<int, std::vector<std::string> >::iterator it;
  if (seq.empty()) {
    std::cout << "No match" << endl;
  } else {
    int needSpace = 0;
    for (it = seq.begin(); it != seq.end(); ++it) {
      std::vector<std::string>::iterator it2;
      std::sort (it->second.begin(), it->second.end());
      for (it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if (!needSpace) {
          std::cout << *it2;
          needSpace = 1;
        } else {
          std::cout << " " << *it2;
        }
      }
    }
  std::cout << endl;
  }
  return counter;
}


int main(int argc, char *argv[]) {

  ifstream oFile;
  oFile.open(argv[1], ios::in);
  if (oFile.is_open()) {
    string segment;
    string dna;
    string max_distance;
    char * tmp;
    std::string line;
    while(getline(oFile, line)) {
      std::stringstream ss(line);
      std::getline(ss, segment, ' ');
      std::getline(ss, max_distance, ' ');
      std::getline(ss, dna, ' ');

      search(segment, dna, atoi(max_distance.c_str()));
    }

    oFile.close();
  }

}
