int: nc = 3;

var 1..nc: arr3;

constraint arr3 != arr4;

solve satisfy;

output ["arr3 = \(arr3)"];
