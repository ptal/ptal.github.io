int: nc = 3;

var 1..nc: arr3;
var 1..nc: arr4;
var 1..nc: arr5;
var 1..nc: arr11;
var 1..nc: arr12;

constraint arr3 != arr4;
constraint arr3 != arr11;
constraint arr4 != arr11;
constraint arr4 != arr12;
constraint arr4 != arr5;
constraint arr11 != arr12;

solve satisfy;
output ["arr3 = \(arr3)\t arr4 = \(arr4)\t arr5 = \(arr5)\n",
        "arr11 = \(arr11)\t arr12 = \(arr12)"];
