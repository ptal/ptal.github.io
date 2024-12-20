from enum import Enum

class Consistency(Enum):
  SAT = 1
  UNSAT = 2
  UNKNOWN = 3

def solve(vars, cons):
  status = propagate(vars, cons)
  if status == Consistency.SAT:
    yield vars
  elif status == Consistency.UNKNOWN:
    yield from branch(vars, cons)

def propagate(vars, cons):
  for (c, p) in cons:
    if not p(vars):
      return Consistency.UNSAT
  return consistency(vars, cons)

def consistency(vars, cons):
  num_sat = 0
  for (c, p) in cons:
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
  for v in vars[x]:
    old = dict([(x, v.copy()) for (x,v) in vars.items()])
    vars[x] = set([v])
    yield from solve(vars, cons)
    vars = old

def select_var(vars):
  for (x, v) in vars.items():
    if len(v) > 1:
      return x

def xNeqY(x, y):
  return (lambda vars: xNeqYConsistence(x,y,vars),
          lambda vars: xNeqYProp(x,y,vars))

def xNeqYConsistence(x,y,vars):
  d = vars[x].isdisjoint(vars[y])
  if d:
    return Consistency.SAT
  elif len(vars[x]) == 1 and len(vars[y]) == 1 and not d:
    return Consistency.UNSAT
  else:
    return Consistency.UNKNOWN

def xNeqYProp(x,y,vars):
  if len(vars[x]) == 1:
    vars[y].difference_update(vars[x])
  elif len(vars[y]) == 1:
    vars[x].difference_update(vars[y])
  return len(vars[x]) > 0 and len(vars[y]) > 0

# X = |Y - Z|
def xEqAbsYMinusZ(x, y, z):
  return (lambda vars: xEqAbsYMinusZConsistence(x,y,z,vars),
          lambda vars: xEqAbsYMinusZProp(x,y,z,vars))

def absXMinusY(x,y,vars):
  r = set()
  for v in vars[x]:
    for w in vars[y]:
      r.add(abs(v - w))
  return r

def xEqAbsYMinusZConsistence(x,y,z,vars):
  r = absXMinusY(y,z,vars)
  if vars[x].isdisjoint(r):
    return Consistency.UNSAT
  elif len(vars[x]) == 1 and len(r) == 1 and vars[x] == r:
    return Consistency.SAT
  else:
    return Consistency.UNKNOWN

# Simple propagation scheme on "x" for the constraint x = |y - z|.
def xEqAbsYMinusZProp(x,y,z,vars):
  r = absXMinusY(y,z,vars)
  vars[x].intersection_update(r)
  return len(vars[x]) > 0 and len(vars[y]) > 0 and len(vars[z]) > 0

# Constrain the variables in vars between s and n excluded to be all different.
def allDifferent(vars, s, n):
  for x in range(s, n):
    for y in range(x+1, n):
      yield xNeqY(x, y)

P = 12
N = 7

I = N*2-1

pitches = dict([(x, set(range(P))) for x in range(N)])
pitchesAllDiff = [c for c in allDifferent(pitches, 0, N)]

intervals = dict([(x, set(range(1,P))) for x in range(N,I)])
intervalsAllDiff = [c for c in allDifferent(intervals, N, I)]

pitchesEqIntervals = [xEqAbsYMinusZ(N+i, i, i+1) for i in range(N-1)]

vars = dict(list(pitches.items()) + list(intervals.items()))
constraints = pitchesAllDiff + intervalsAllDiff + pitchesEqIntervals

for sol in solve(vars, constraints):
  for i in range(N):
    print(sol[i], end=" ")
  print("")
  break
