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

def consistency(vars, cons):
  num_sat = 0
  for c in cons:
    r = c(vars)
    if r == Consistency.UNSAT:
      return Consistency.UNSAT
    elif r == Consistency.SAT:
      num_sat += 1
  if num_sat == len(cons):
    return Consistency.SAT
  else:
    return Consistency.UNKNOWN

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

def xNeqYConsistence(x,y,vars):
  if vars[x].isdisjoint(vars[y]):
    return Consistency.SAT
  elif len(vars[x]) == 1 and len(vars[y]) == 1 and vars[x] == vars[y]:
    return Consistency.UNSAT
  else:
    return Consistency.UNKNOWN

vars = dict(
  x=set(range(2)),
  y=set(range(3)),
  z=set(range(2)))

constraints = [xNeqY("x", "y")]

for sol in solve(vars, constraints):
  print(sol)
