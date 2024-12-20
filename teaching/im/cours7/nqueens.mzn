include "alldifferent.mzn";
int: N = 40;
array[1..N] of var 1..N: queens;

% Different columns.
% constraint forall(l1,l2 in 1..N where l1 < l2)
%                  (queens[l1] != queens[l2]);
% % Different diagonals.
% constraint forall(l1,l2 in 1..N where l1 < l2)
%                  (l2 - l1 != abs(queens[l1] - queens[l2]));

constraint alldifferent(queens);
constraint alldifferent(i in 1..N)(queens[i] + i);
constraint alldifferent(i in 1..N)(queens[i] - i);

solve satisfy;
output [show(queens)];
