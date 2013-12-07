class Expression(object):
  
  lOperators = ['+', '-', '/', '*']
  
  def __init__(self, psExpression):
    """ Ok """
    self._lStack = psExpression.split()
    self._lStack.reverse()
    self._lStackOperande = []
    
  def computeExpression(self):
    
    for loItem in self._lStack :
      if loItem in self.lOperators :
        lfOperande1 = float(self._lStackOperande.pop(0))
        lfOperande2 = float(self._lStackOperande.pop(0))
        
        if loItem == '+' :
          lfResult = lfOperande1 + lfOperande2
        elif loItem == '-' :
          lfResult = lfOperande1 - lfOperande2
        elif loItem == '/' :
          lfResult = lfOperande1 / lfOperande2
        elif loItem == '*' :
          lfResult = lfOperande1 * lfOperande2
        
        self._lStackOperande.insert(0, lfResult)
      else :
        self._lStackOperande.insert(0, loItem)
        
    return self._lStackOperande.pop(0)

if __name__ == '__main__' :
  a = Expression('* + 3 2 4')
  print a.computeExpression()