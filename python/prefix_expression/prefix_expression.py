def isOperator(char):
  return char in ["+", "*", "/"]

def compute(operator, operand1, operand2):
  if operator == "+":
    # no problem with associative
    return int(operand1) + int(operand2)
  if operator == "*":
    # associative
    return int(operand1) * int(operand2)
  if operator == "/":
    # no associative
    return int(operand1) / int(operand2)

def computeExpression(line):
  # queue do not need to reverse because pop already dequeue the last one.
  queue = line.split()
  operands = []
  while len(queue):
    char = queue.pop()
    if isOperator(char):
      operands.append(compute(char, operands.pop(), operands.pop()))
    else:
      operands.append(char)


  return operands.pop()

if __name__ == "__main__":

  test_cases = open('prefix_input.txt', 'r')

  for test in test_cases:
    if test.strip():
      #sys.stdout.write(str(fib.get(int(test))))
      print computeExpression(test)
  test_cases.close()

