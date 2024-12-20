from enum import Enum

class Consistency(Enum):
  SAT = 1
  UNSAT = 2
  UNKNOWN = 3

def solve(vars, cons):
  status = consistency(vars, cons)
  if status == Consistency.SAT:
    yield vars
  elif status == Consistency.UNKNOWN:
    yield from branch(vars, cons)

# Return SAT if all the constraints in "cons" are satisfied with regards to "vars".
#        UNSAT if one constraint is unsatisfied.
#        UNKNOWN otherwise
def consistency(vars, cons):
  ...

def branch(vars, cons):
  x = select_var(vars)
  old = vars[x]
  for v in vars[x]:
    vars[x] = set([v])
    yield from solve(vars, cons)
  vars[x] = old

def select_var(vars):
  for (x, v) in vars.items():
    if len(v) > 1:
      return x

def xNeqY(x, y):
  return lambda vars: xNeqYConsistence(x,y,vars)

# Return a value in Consistency by checking if the constraint "x != y".
def xNeqYConsistence(x,y,vars):
  ...

vars = dict(
  x=set(range(2)),
  y=set(range(3)),
  z=set(range(2)))

constraints = [xNeqY("x", "y")]

for sol in solve(vars, constraints):
  print(sol)
