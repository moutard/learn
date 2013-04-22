class A(object):
  def __init__(self):
    self.value = 0

  def my_method(self):
    print 'my_method'

  def my_function():
    print 'my_function'

  @staticmethod
  def my_method_static():

if __name__ == "__main__":
  a = A()
  a.my_method()
  A.my_method_static()

