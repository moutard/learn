
def g():
  """This is a generator, it has 3 methods :
  - next
  - send
  - throw
  """
  yield 1
  yield 2
  yield 3

for x in g():
  print x

gi = g()
print next(gi)

for x in g():
  print next(gi)

