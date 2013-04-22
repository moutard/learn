def f1(arg):
  return arg + 2

def f2:
  return 3


@f1(arg)
@f2
def func(): pass
#is equivalent to:

def func(): pass
func = f1(arg)(f2(func))
