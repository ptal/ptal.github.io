def permutation(n, dom):
  solve([], n, dom)

def solve(sol, n, dom):
  if n == len(sol):
    print(sol)
  else:
    for v in range(dom):
      solve(sol + [v], n, dom)

permutation(3, 2)
