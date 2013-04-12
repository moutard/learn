import unittest

from fibonnaci import *

class FibonnaciTest(unittest.TestCase):

  def test_0(self):
    self.assertEqual(0, Fibonnaci().get(0))

  def test_1(self):
    self.assertEqual(1, Fibonnaci().get(1))

  def test_2(self):
    self.assertEqual(1, Fibonnaci().get(2))
    self.assertEqual(1, Fibonnaci().get_no_recursion(2))

  def test_5(self):
    self.assertEqual(5, Fibonnaci().get(5))
    self.assertEqual(5, Fibonnaci().get_no_recursion(5))

  def test_12(self):
    self.assertEqual(144, Fibonnaci().get(12))
    self.assertEqual(144, Fibonnaci().get_no_recursion(12))

  def test_12_(self):
    fib = Fibonnaci()
    self.assertEqual(1, fib.get(1))
    self.assertEqual(5, fib.get(5))

    self.assertEqual(144, fib.get(12))
    self.assertEqual(fib._MEMOIZE_FIB[12], 144)
    self.assertEqual(fib._MEMOIZE_FIB[6], 8)
    self.assertEqual(8, fib.get(6))

  def test_product_matrix(self):
    show(matrix_product([[1,1],[1,1]], [[1,1],[1,1]]))
    self.assertEqual(matrix_product([[1,1],[1,1]], [[0,0],[0,0]]), [[0,0],[0,0]])


  def test_binary_mult(self):
    fib = FibMatrix()
    self.assertEqual(fib.binary_mult([[1,1],[1,0]], 2), [[2,1],[1,1]])
    self.assertEqual(fib.binary_mult([[1,1],[1,0]], 3), [[3,2],[2,1]])
    self.assertEqual(fib.binary_mult([[1,1],[1,0]], 4), [[5,3],[3,2]])
    self.assertEqual(fib.binary_mult([[1,1],[1,0]], 5), [[8,5],[5,3]])

  def test_fibonnaci_using_matrix(self):
    fib = FibMatrix()
    self.assertEqual(8, fib.get(6))

if __name__ == "__main__":
  unittest.main()
