
lPreComputedValues = []
def initPrecomputedValues(l1, l2):
  for i in xrange(0, l1):
    lPreComputedValues.append([-1]*l2)

def longuestSubSequence(sString1, sString2, i, j):
  if i < 0 or j < 0:
    return 0
  if lPreComputedValues[i][j] != -1:
    return lPreComputedValues[i][j]
  if sString1[i] == sString2[j]:
    lPreComputedValues[i][j] =  1 + longuestSubSequence(sString1, sString2, i-1, j-1)
    return lPreComputedValues[i][j]
  else :
    lPreComputedValues[i][j] = max(longuestSubSequence(sString1, sString2, i-1, j),
        longuestSubSequence(sString1, sString2, i, j-1))
    return lPreComputedValues[i][j]

if __name__ == "__main__" :
  sString1 = "abaac"
  sString2 = "acba"
  initPrecomputedValues(len(sString1), len(sString2))
  i = longuestSubSequence(sString1, sString2, len(sString1) - 1, len(sString2) - 1)
  print i


