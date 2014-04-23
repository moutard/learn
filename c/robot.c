#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  /**
   * More generally this solution for a grid with nxn square is
   * (2(n-1) (n-1)) (binomial coefficient)
   *
   * To arrive to this conclusion, we can draw the grid as a tree (grid until the
   * diagonal)
   *
   *        x0
   *       / \
   *     x1  x2
   *    / \  / \
   *   x3  x4  x5
   *
   *   if there is N1 paths to x1 then there is N2 paths to x2
   *   then there is
   *    N1 paths to x3
   *    N2 paths to x5
   *    N1 + N2 paths to x4
   *
   *    has N0 is 1
   *    Whe see the formule of the binomial coefficient.
   *
   *    so to arrive to
   *     - x3 there is (2 0) = 1 paths (2
   *     - x4 there is (2 1) = 2 paths (2
   *     - x4 there is (2 2) = 1 paths (2
   *
   *    we generalize easily with a bigger tree.
   *
   *    rq: at this point the number of leaves in this degenerated tree (degenerated
   *    because 2 parents can point to the same child) is the sum of binomial
   *    coefficient that is
   *    sum ((n-1) k) over k  = 2^(n-1)  (1+1)^n
   *
   *    For the other part of the tree it's symetric, so when you have N4 paths to
   *    arrive to x4 then you have N4 path to arrive to the end.
   *
   *    so the number of paths that goes throught x4 is N4^2
   *    means ((n-1) k)^2
   *
   *    The sum of binomial coefficient square is the number of paths.
   *    easy to compute using vandermonde indentity
   *
   *    sum(over k) (n k)^2 = (2n n)
   *
   *    AN: here the grid is 4
   *    (2(4-1) (4-1)) = (6 3) = 70
   */
  printf("70");
}
