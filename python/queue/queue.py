
class MyQueue():

  _SIZE = 10
  _NULL_VALUE = -1

  def __init__(self):
    self._lData = [self._NULL_VALUE]*self._SIZE
    self._iStartIndex = 0
    self._iSize = 0

  def enqueue(self, iElement):
    if self._iSize >= len(self._lData):
      # there is available space.
      # Create a new array and fill it with the old value.
      lTempData = [self._NULL_VALUE]*self._SIZE*2
      for i in xrange(0, self._iSize):
        iNextIndex = (self._iStartIndex + i) % len(self._lData)
        lTempData[i] = self._lData[iNextIndex]
      self._iStartIndex = 0
      self._lData = lTempData
    # there is avaiblable space.
    iNextIndex = (self._iStartIndex + self._iSize) % len(self._lData)
    self._lData[iNextIndex] = iElement
    self._iSize += 1


  def dequeue(self):
    if self._iSize == 0:
      raise Exception('nothing to dequeue')
    else:
      oResult = self._lData[self._iStartIndex]
      self._lData[self._iStartIndex] = self._NULL_VALUE
      self._iStartIndex = (self._iStartIndex + 1) % len(self._lData)
      self._iSize = self._iSize - 1
      return oResult

  def _print(self):
    s = ""
    for i in self._lData:
      s += str(i) + " "
    print "start: %s\n size: %s\n with content: %s" % (self._iStartIndex, self._iSize, s)


if __name__ == "__main__":
  oQueue = MyQueue()
