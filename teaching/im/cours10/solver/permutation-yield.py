def permutation(n, dom):
  yield from solve([], n, dom)

def solve(sol, n, dom):
  if n == len(sol):
    yield sol
  else:
    for v in range(dom):
      yield from solve(sol + [v], n, dom)

for sol in permutation(3, 2):
  print(sol)
