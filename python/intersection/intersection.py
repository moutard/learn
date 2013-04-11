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



