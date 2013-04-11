"""Challenge Description:

You are given two sorted list of numbers(ascending order). The lists themselves are comma delimited and the two lists are semicolon delimited. Print out the intersection of these two sets.

Input sample:

File containing two lists of ascending order sorted integers, comma delimited, one per line. e.g.

1,2,3,4;4,5,6
7,8,9;8,9,10,11,12
Output sample:

Print out the ascending order sorted intersection of the two lists, one per line
e.g.

4
8,9
"""

def explode(sInput):
  return [int(number) for number in sInput.split(',')]

def intersection(lNumbersA, lNumbersB):
  """Return a list of common elements in 2 lists sorted in asc order.
    Args:
    - lNumbersA: list of integer sorted by asc order
    - lNumbersB: lsit of integer sorted by asc order
  """
  lIntersection = [] # list that accumulates the intersion elements of the 2 lists

  iIndexA = 0
  iIndexB = 0

  while(iIndexA < len(lNumbersA) and iIndexB < len(lNumbersB)):
    if(lNumbersA[iIndexA] == lNumbersB[iIndexB]):
      lIntersection.append(lNumbersA[iIndexA])
      iIndexA += 1
      iIndexB += 1
    elif(lNumbersA[iIndexA] < lNumbersB[iIndexB]):
      iIndexA += 1
    else:
      iIndexB += 1

  return lIntersection



