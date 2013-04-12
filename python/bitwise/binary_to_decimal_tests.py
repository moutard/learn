import unittest
from decimal_to_binary import *

class DecimalTest(unittest.TestCase):

  def test_2(self):
    self.assertEqual(toBinary(2), "10")

  def test_3(self):
    self.assertEqual(toBinary(3), "11")

  def test_1029(self):
    self.assertEqual(toBinary(1029), "10000000101")

if __name__ == "__main__":
  unittest.main()
