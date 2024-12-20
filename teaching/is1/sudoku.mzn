include "alldifferent.mzn";
int: N = 9;
array[1..N,1..N] of var 1..N: sudoku;
constraint forall(l in 1..N)
  (alldifferent(c in 1..N)(sudoku[l,c]));% | c in 1..N]));
constraint forall(c in 1..N)
  (alldifferent([sudoku[l,c] | l in 1..N]));
constraint forall(l, c in {1,4,7})
  (alldifferent([sudoku[l + sl, c + sc] | sl,sc in 0..2]));

solve satisfy;
output [show2d(sudoku)];

sudoku=[|
_, _, _, _, _, _, _, _, _|
_, _, 8, 4, _, 1, _, 7, _|
_, _, _, _, 8, 5, _, 3, _|
_, 2, 6, 8, _, 9, _, 4, _|
_, _, 7, _, _, _, 9, _, _|
_, 5, _, 1, _, 6, 3, 2, _|
_, 4, _, 6, 1, _, _, _, _|
_, 3, _, 2, _, 7, 6, 9, _|
_, _, _, _, _, _, _, _, _|
|];
