
class TreeNode(object):

  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None


class Tree(object):

  def __init__(self):
    self.root = None

  def insert(self, value):
    self.root = self._insert(self.root, value)

  def _insert(self, treeNode, value):
    """We have to return the node because according to python doc, even
    reference are passed by value, so you can't modify directly the reference
    to the node in the function. (you can only modify it's content.
    That's exactly the same problem than c++, but in c++ we can forced the pointer
    to be passed by reference. Here we can't.
    """
    if treeNode == None:
      return TreeNode(value)
    elif treeNode.value > value:
      treeNode.left = self._insert(treeNode.left, value)
      return treeNode
    else :
      treeNode.right = self._insert(treeNode.right, value)
      return treeNode

  def preOrder(self):
    self._preOrder(self.root)

  def _preOrder(self, treeNode):
    if treeNode != None:
      self._preOrder(treeNode.left)
      print treeNode.value
      self._preOrder(treeNode.right)

  def inOrder(self):
    self._inOrder(self.root)

  def _inOrder(self, treeNode):
    if treeNode != None:
      print treeNode.value
      self._inOrder(treeNode.left)
      self._inOrder(treeNode.right)

  def rotateLeft(self, treeNode):
    if treeNode != None:
      newRoot = treeNode.left
      treeNode.left = newRoot.right
      newRoot.right = treeNode
      return newRoot
    else:
      return treeNode

if __name__ == "__main__":
  t = Tree()
  t.insert(8)
  t.insert(10)
  t.insert(5)
  t.insert(6)
  t.insert(2)
  t.insert(12)
  #t.preOrder()
  t.inOrder()
  t.root = t.rotateLeft(t.root)
  print "------"
  t.inOrder()
