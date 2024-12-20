int: n = 3;
int: c = 3;
int: p = 10;

array[1..n] of var 1..c: cost;
var 1..n*c: total = sum(cost);
array[1..n] of var 1..c*2: double_cost =
  [cost[i] * 2 | i in 1..n];

array[1..n, 1..n] of 0..p: neighbors;

array[1..n] of 0..p*n: empathy =
  [sum([neighbors[i,j] | j in 1..n where i != j])
   | i in 1..n];


var 0..p*n*n: global_empathy =
  sum(i,j in 1..n where i != j)
     (neighbors[i,j]);
  
 array[1..n] of var 1..n: t;
constraint forall(i,j in 1..n where i < j)
                 (t[i] != t[j]);
  
solve satisfy;

output [show(empathy), show(global_empathy), show(t)];
