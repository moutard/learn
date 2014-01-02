import unittest

from queue import MyQueue

class TestQueue(unittest.TestCase):

  def setUp(self):
    self._oQueue = MyQueue()

  def test_dequeue_empty(self):
    self.assertRaises(Exception ,self._oQueue.dequeue)

  def test_enqueue_out_of_bound(self):
    self._oQueue.enqueue(1)
    self._oQueue.enqueue(2)
    self._oQueue.enqueue(3)
    self._oQueue.enqueue(4)
    self._oQueue.enqueue(5)
    self._oQueue.enqueue(6)
    self._oQueue.enqueue(7)
    self._oQueue.enqueue(8)
    self._oQueue.enqueue(9)
    self._oQueue.enqueue(10)
    self._oQueue.enqueue(11)
    self._oQueue.enqueue(12)
    oResult = self._oQueue.dequeue()
    self.assertEqual(1, oResult)
    #self.assertRaises(Exception, self._oQueue.enqueue, 1)

  def test_enqueue_out_of_bound(self):
    self._oQueue.enqueue(1)
    self._oQueue.enqueue(2)
    oResult = self._oQueue.dequeue()
    self._oQueue.enqueue(3)
    self._oQueue.enqueue(4)
    self._oQueue.enqueue(5)
    self._oQueue.enqueue(6)
    self._oQueue.enqueue(7)
    self._oQueue.enqueue(8)
    self._oQueue.enqueue(9)
    self._oQueue.enqueue(10)
    self._oQueue.enqueue(11)
    self._oQueue.enqueue(12)
    oResult = self._oQueue.dequeue()
    self.assertEqual(2, oResult)
    #self.assertRaises(Exception, self._oQueue.enqueue, 1)
  def test_dequeue(self):
    self._oQueue.enqueue(1)
    oResult = self._oQueue.dequeue()
    self.assertEqual(1, oResult)

  def test_complexe_dequeue(self):
    self._oQueue.enqueue(1)
    self._oQueue.enqueue(2)
    self._oQueue.enqueue(3)
    oResult = self._oQueue.dequeue()
    self.assertEqual(1, oResult)
    self._oQueue.enqueue(4)
    self._oQueue.enqueue(5)
    oResult = self._oQueue.dequeue()
    self.assertEqual(2, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(3, oResult)
    self._oQueue._print()
    oResult = self._oQueue.dequeue()
    self.assertEqual(4, oResult)

  def test_complexe_dequeue(self):
    self._oQueue.enqueue(1)
    self._oQueue.enqueue(2)
    self._oQueue.enqueue(3)
    oResult = self._oQueue.dequeue()
    self._oQueue.enqueue(4)
    self._oQueue.enqueue(5)
    oResult = self._oQueue.dequeue()
    oResult = self._oQueue.dequeue()
    self._oQueue.enqueue(6)
    self._oQueue.enqueue(7)
    self._oQueue.enqueue(8)
    self._oQueue.enqueue(9)
    self._oQueue.enqueue(1)
    self._oQueue.enqueue(2)
    oResult = self._oQueue.dequeue()
    self.assertEqual(4, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(5, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(6, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(7, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(8, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(9, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(1, oResult)
    oResult = self._oQueue.dequeue()
    self.assertEqual(2, oResult)



if __name__ == '__main__':
  unittest.main()
