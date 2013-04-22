def foo(key, value, mydict={}):  # Danger: shared reference to one dict for all calls
    mydict[key] = value
    return mydict

if __name__ == "__main__":
  d = foo("a", 1)
  d = foo("b", 2)
  print d
