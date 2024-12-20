var 0..1: A;
var 0..1: B;
var 0..1: C;

var 0..3: T;

constraint T = A + B + C;

% constraint A = 0 -> T = 1;
% constraint A = 1 -> T != 1;
% constraint B = 0 -> T = 2;
% constraint B = 1 -> T != 2;
% constraint C = 0 -> T = 3;
% constraint C = 1 -> T != 3;

constraint A = 1 xor T = 1;
constraint B = 1 xor T = 2;
constraint C = 1 xor T = 3;

solve satisfy;
