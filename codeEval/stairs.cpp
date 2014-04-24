#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
/**
 * Problem
 * even for 64 bits machine, unsigned long is limited to 2^64.
 * So after the 93th fibonnaci number it becomes to big.
 *
 * for intance
 * fib(1000) ~= 4.10^208 (> 2^625 !)
 *
 * So you need to deal with big integer !
 * There are a lot of libraries to work with big int, but as we only want to
 * deal with addition, and print. We will create a specific class.
 */

class BigInt {
  public:
    BigInt();
    BigInt(const BigInt &);
    BigInt(const std::string &);
    ~BigInt();
    BigInt & operator+=(const BigInt & other) {
      char retained = 0;
      unsigned int current_size = size < other.size ? other.size : size;
      for (unsigned int i = 0; i < current_size; ++i) {
        char digit = digits[i] + other.digits[i] + retained;
        if (digit > 9) {
          digits[i] = digit - 10;
          retained = 1;
        } else {
          digits[i] = digit;
          retained = 0;
        }
      }
      if (retained) {
        digits[current_size] = retained;
        current_size++;
      }
      size = current_size;
      // the retained can influenced the length of 1!
      return *this;
    };
    unsigned int isZero() {return (size == 1 && digits[0] == 0);};

    ostream& print (ostream& os) const {
      for (unsigned int i = 0; i < size; ++i) {
        os << digits[size - 1 - i];
      }
      return os;
    };
  private:
    friend ostream&  operator<<( ostream& os, const BigInt & c );

    static const unsigned int MAX_SIZE = 300;
    unsigned int digits[300];
    unsigned int size;
};

BigInt::BigInt() : size(1) {
  for (unsigned int i = 0; i < MAX_SIZE; ++i) {
    digits[i] = 0;
  }
}

BigInt::BigInt(const std::string & s) : size(s.size()) {
  for (unsigned int i = 0; i < MAX_SIZE; ++i) {
    digits[i] = 0;
  }
  for (unsigned int i = 0; i < size; ++i) {
    digits[i] = atoi(s.substr(size - 1 - i, 1).c_str());
  }
}

BigInt::BigInt(const BigInt & oBi) {
  size = oBi.size;
  for (unsigned int i = 0; i < MAX_SIZE; ++i) {
    digits[i] = oBi.digits[i];
  }
}

BigInt::~BigInt() {

}

const BigInt operator+(const BigInt & a, const BigInt & b) {
  BigInt ret(a);
  ret += b;
  return ret;
}

ostream& operator<<(ostream& os, const BigInt & c) {
  return c.print(os);
}
BigInt FIB[1024];

BigInt fibonacci (unsigned int i) {
  if (i < 1024 && !FIB[i].isZero()) return FIB[i];
  if (i == 0) return BigInt("0");
  if (i == 1) return BigInt("1");
  if (i == 2) return BigInt("1");
  if (i == 3) return BigInt("2");
  FIB[i] = fibonacci(i-1) + fibonacci(i-2);
  return FIB[i];
}


int main(int argc, char * argv[]) {

  for (unsigned int i = 0; i < 1024; ++i) {
    FIB[i] = BigInt();
  }
  BigInt i("3");
  BigInt j("456");
  i += j;
  BigInt k = i + j;
  FILE * oFile = fopen(argv[1], "r");
  char line[8];

  while(fgets(line, 8, oFile) != NULL) {
    cout << fibonacci(atoi(line)+1) << endl;
  }

  fclose(oFile);

}
