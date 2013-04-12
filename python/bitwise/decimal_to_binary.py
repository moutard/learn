def toBinary(n):
  binary = ""
  while(n != 0):
    binary = str(n & 1) + binary
    n = n >> 1
  return binary
