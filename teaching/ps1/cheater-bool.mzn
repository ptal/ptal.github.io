var bool: A;
var bool: B;
var bool: C;

var int: T = bool2int(A) + bool2int(B) + bool2int(C);

constraint not A <-> T = 1;
constraint not B <-> T = 2;
constraint not C <-> T = 3;

solve satisfy;
