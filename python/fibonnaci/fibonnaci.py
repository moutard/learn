import sys
def zero(m,n):
  """Create a matrix of size m*n full with 0."""
  new_matrix = [[0 for row in range(n)] for col in range(m)]
  return new_matrix

def matrix_product(matrix1, matrix2):
  """Make the produt of 2 matrix."""
  # create a matrix zero that will accumulate values.
  new_matrix = zero(len(matrix1),len(matrix2[0]))

  # the commun size is len(matrix2) len(matrix1[0])
  for i in range(len(matrix1)):
    for j in range(len(matrix2[0])):
      for k in range(len(matrix2)):
        new_matrix[i][j] += matrix1[i][k]*matrix2[k][j]
  return new_matrix

def show(matrix):
  # Print out matrix
  print
  for col in matrix:
    print col
  print '__'

class FibMatrix:
  def __init__(self):
    self._sub = [[1,1],[1,0]]

  def binary_mult(self, M, n):
    if n == 1:
      return M
    elif n % 2 == 0 :
      k = self.binary_mult(M, n/2)
      return matrix_product(k, k)
    else:
      k = self.binary_mult(M, n/2)
      return matrix_product(matrix_product(k, k), M)

  def get(self, n):
    if n == 0:
      return 0
    else :
      return self.binary_mult(self._sub, n)[0][1]


if __name__ == "__main__":

  test_cases = open('fibonnaci_input.txt', 'r')

  fib = FibMatrix()
  for test in test_cases:
    if test.strip():
      #sys.stdout.write(str(fib.get(int(test))))
      print fib.get(int(test))
  test_cases.close()

