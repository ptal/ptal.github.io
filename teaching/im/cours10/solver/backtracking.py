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

def consistency(vars):
  num_assigned = 0
  for v in vars.values():
    if len(v) == 0:
      return Consistency.UNSAT
    elif len(v) == 1:
      num_assigned += 1
  if num_assigned == len(vars):
    return Consistency.SAT
  else:
    return Consistency.UNKNOWN

def branch(vars):
  x = select_var(vars)
  old = vars[x]
  for v in vars[x]:
    vars[x] = set([v])
    yield from solve(vars)
  vars[x] = old

def select_var(vars):
  for (x, v) in vars.items():
    if len(v) > 1:
      return x

solve(dict(
  x=set(range(2)),
  y=set(range(3)),
  z=set(range(1))))
