def isUglyNumber(piNumber):
  
  # divisible par 
  return 0

def isDivisibleBy2(piNumber):
  lsNumber = str(piNumber)
  
  if lsNumber[ len(lsNumber) - 1 ] in ['0', '2', '4', '6', '8'] :
    return True
  else :
    return False


def isDivisibleBy3(piNumber):
  lsNumber = str(piNumber)
  
  if len(lsNumber) == 1 :
    if lsNumber in ['3', '6', '9'] :
      return True
    else :
      return False
  else :
    liNumber = 0
    for lsItem in lsNumber :
      liNumber += int(lsItem)

    return isDivisible3(liNumber)


def isDivisibleBy5(piNumber):
  lsNumber = str(piNumber)

  if lsNumber[ len(lsNumber) - 1 ] in ['0', '5']:
    return True
  else : 
    return False


def isDivisibleBy7(piNumber):
  lsNumber = str(piNumber)

  if len(lsNumber) == 1:
    if lsNumber in ['0', '7']:
      return True
    else :
      return False
  else :
    liNumber = int(lsNumber[0:len(lsNumber)-1])
    liNumber -= 2*int(lsNumber[len(lsNumber) -1])
    return isDivisibleBy7(liNumber)

def isModulo7(piNumber):
  if (piNumber % 7) == 0 :
    return True
  else :
    return False
     
if __name__ == "__main__":
  liNumber = 7*123456789
  print isDivisibleBy7(liNumber)
  
  from timeit import Timer
  t = Timer("isDivisibleBy7(7*123456789)", "from __main__ import isDivisibleBy7")
  print "using my own method"
  print t.timeit()
  
  print 'using modulo'
  p = Timer("isModulo7(7*123456789)", "from __main__ import isModulo7")
  print p.timeit()