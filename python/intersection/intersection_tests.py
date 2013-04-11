import unittest
from intersection import *

class IntersectionTest(unittest.TestCase):
  def test_explode(self):
    self.assertEqual([1,2,3], explode("1,2,3"))

  def test_intersection(self):
    self.assertEqual([1,2,3], intersection(
      [1,2,3,4], [1,2,3]))

  def test_intersection_complexe(self):
    self.assertEqual([6,8], intersection(
      [1,2,3,4,6,8,9,19], [6,7,8]))

if __name__ == "__main__":
  unittest.main()
