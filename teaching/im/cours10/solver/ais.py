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

# X = |Y - Z|
def xEqAbsYMinusZ(x, y, z):
  return lambda vars: xEqAbsYMinusZConsistence(x,y,z,vars)

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
