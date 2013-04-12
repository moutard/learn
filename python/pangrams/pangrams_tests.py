import unittest
from pangrams import *

class PangramsTests(unittest.TestCase):
  def test_is_pangram(self):
    self.assertEqual(missingLetters("A quick brown fox jumps over the lazy dog"),
      [])

  def test_is_pangram(self):
    self.assertEqual(missingLetters("A slow yellow fox crawls under the proactive dog"),
      ['b', 'j', 'k', 'm', 'q', 'z'])

  def test_print_result(self):
      printResult(missingLetters("A slow yellow fox crawls under the proactive dog"))
      printResult(missingLetters("A quick brown fox jumps over the lazy dog"))

if __name__ == "__main__":
  unittest.main()
