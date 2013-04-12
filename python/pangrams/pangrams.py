import sys
def printResult(l):
  if(len(l)== 0):
    sys.stdout.write('NULL')
  for sLetter in l:
    sys.stdout.write(sLetter)
  print

def missingLetters(sInput):
  alphabet = "a b c d e f g h i j k l m n o p q r s t u v w x y z".split(" ")
  for sLetter in sInput:
    iIndex = ord(sLetter)
    if(ord('A') <= iIndex and iIndex <= ord('Z')):
      iIndex = ord(sLetter) - ord('A')
      alphabet[iIndex] = 0
    elif(ord('a') <= iIndex and iIndex <= ord('z')):
      iIndex = ord(sLetter) - ord('a')
      alphabet[iIndex] = 0

  return [sA for sA in alphabet if sA != 0]

if __name__ == "__main__":

  test_cases = open('pangrams_input.txt', 'r')

  for line in test_cases:
    if line.strip():
      printResult(missingLetters(line))
  test_cases.close()
