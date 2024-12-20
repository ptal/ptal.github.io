int: nc = 3;

var 1..nc: dis3;

constraint dis3 != dis4;

solve satisfy;

output ["dis3 = \(dis3)"];
