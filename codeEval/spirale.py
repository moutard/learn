def spirale(psValue):
  llValue = psValue.split()
  liN = int(llValue.pop(0))
  liM = int(llValue.pop(0))
  llMatrix = []
  
  print llValue
  while liN > 0 :
    printContour(llValue, liN, liM)
    liN-=1
    liM-=1
    

def printContour(plMatrix, piLargeur, piHauteur):
  
  # Print First raw
  for liColumnIndex in range( 0, piLargeur ):
    print plMatrix[liColumnIndex]
  
  # Print Last Column
  for liRowIndex in range( 0, piHauteur - 1 ):
    print plMatrix[(liRowIndex + 1)*piLargeur + piLargeur -1]
  
  # Print Last Row
  for liColumnIndex in range( 0, piLargeur - 1 ):
    print plMatrix[piHauteur*(piLargeur - 1) + piLargeur - 1 - liColumnIndex - 1]
  
  # Print First Column
  for liRowIndex in range( 0, piHauteur - 2 ):
    print plMatrix[(piHauteur -1 - liRowIndex)]
    

def spirale2():
  return 1

    
if __name__ == '__main__':
  spirale('3 3 1 2 3 4 5 6 7 8 9')
  
    