#include <string>
#include <stdio.h>
using namespace std;

// (1/B) is the smallest possible unit B = 2^20.
// The idea is instead of working with unit we will work with a new unit call
// drop. 1 unit = B drops.
#define B (1<<20)

// Contains amount of each glasses in drops. The capacity of a glass is :
// 2 units = 2*B drops.
// int glass_capacity = 2*B;
int amount[30][30];

class Champagne {
  public:
  string howMuch(int height, int glass, int units) {
    int i, j, numerator, denominator;

    // The first glass receive all the liquide. (we know that it mays overflow,
    // but for the moment just imagine than it can receive the whole units.)
    amount[0][0] = units*B;

    for(i=0; i<=height; i++) for(j=0; j<=i; j++) {

      // We are currently in the glass [i][j].

      // The overflow is the amount of the glass minus it's capacity.
      int overflow = amount[i][j]-2*B;
      printf("%d %d=%d\n", i, j, amount[i][j]);

      // If there is an overlflow dispatch it to the glasses below.
      if (overflow > 0) {
        amount[i+1][j] += overflow/2;
        amount[i+1][j+1] += overflow/2;
        // Remove the overflow of the glass (the current glass that is now full)
        amount[i][j] -= overflow;
      }
      // Check if we find the right glass.
      // glass == 0 we find the right one, as we are descending the pyramid
      // we know that this glass will stay intact.
      glass--; if (!glass) goto out;
    }

    out:
    // Using goto i and j seems still defined. even if we are out of the block.
    numerator = amount[i][j];
    denominator = B*2;
    // Handle execption, like glass empty or full.
    if (!numerator) return "0/1";
    if (numerator == denominator) return "1/1";
    // Simplify the fraction.
    while(numerator%2 == 0 && denominator%2 == 0) numerator/= 2,denominator/=2;
    // Print the fraction.
    char buf[100];
    sprintf(buf, "%d/%d", numerator, denominator);
    return buf;
  }
};

/*
Problem Statement
    	Before you lies a tower of champagne glasses that must be filled. Each glass rests upon exactly 2 other glasses beneath it, with the exception of the lowest row, which sits on the table. An example of a 5 glass tall tower is shown below:
                             1
                           2   3
                         4   5   6
                       7   8   9   10
                    11  12  13   14   15
Each glass can hold 2 units of champagne, and if more than 2 units of champagne fall into any glass, all but 2 of the units will overflow equally into the two glasses below it. Thus, all of the champagne poured into glass 1 after the first 2 units will fall equally into glasses 2 and 3. Once 2 and 3 overflow they will each, independently, distribute the champagne into the two glasses beneath them. At that point glass 5 will be receiving champagne from both glasses 2 and 3. Glass 4 will be receiving champagne from just glass 2, and glass 6 will be receiving champagne from just glass 3.

Given the height of the tower, the number of units poured into glass 1, and the number of a particular glass, return what fraction of that glass is full. Your solution should be a reduced fraction (lowest terms) in the form "numerator/denominator" with no leading zeros in either the numerator or denominator. Full glasses are denoted by "1/1" whereas empty glasses are denoted "0/1". The glasses are numbered in the same way as above, namely left to right, top to bottom. Note, once a glass on the bottom layer is full, extra champagne will just spill onto the table.


Definition

Class:	Champagne
Method:	howMuch
Parameters:	int, int, int
Returns:	String
Method signature:	String howMuch(int height, int glass, int units)
(be sure your method is public)


Notes
-	Glass 1 is in the first row. The glass beneath it, on its left side, is glass 2. More generally, if glass i is in row j the glass beneath it, on its left side, if it exists, is glass i+j.

Constraints
-	height must be between 1 and 20 inclusive
-	glass must be a valid glass number given the value of height
-	units must be between 1 and 300 inclusive

Examples
0)

1
1
1
Returns: "1/2"
Pouring only 1 unit will fill the first and only glass half way.
1)

2
2
2
Returns: "0/1"
The top glass is full, but no champagne has spilled into glass 2.
2)

2
3
3
Returns: "1/4"
The top glass is full and one unit of champagne has spilled out of it. This spilled champagne is evenly distributed between glasses 2 and 3.
3)

3
4
7
Returns: "1/8"
Pouring 6 units causes glasses 1 through 3 to be full. The seventh unit of champagne will make its way to glasses 4 through 6.
4)

3
5
7
Returns: "1/4"
5)

20
204
300
Returns: "5581/131072"
6)

20
204
299
Returns: "8663/262144"
*/
