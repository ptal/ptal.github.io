from enum import Enum

class Consistency(Enum):
  SAT = 1
  UNSAT = 2
  UNKNOWN = 3

def solve(vars):
  status = consistency(vars)
  if status == Consistency.SAT:
    yield print(vars)
  elif status == Consistency.UNKNOWN:
    yield from branch(vars)

# Return SAT if all the variables are assigned (cardinality of 1).
#        UNSAT if one variable has an empty domain.
#        UNKNOWN otherwise
def consistency(vars):
  ...

# Recursively assign a variable 'x' to a value 'v' in its domain.
def branch(vars):
  ...

solve(dict(
  x=set(range(2)),
  y=set(range(3)),
  z=set(range(1))))
