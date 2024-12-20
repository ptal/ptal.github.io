int: nc = 3;

var 1..nc: dis3;
var 1..nc: dis4;
var 1..nc: dis5;
var 1..nc: dis11;
var 1..nc: dis12;

constraint dis3 != dis4;
constraint dis3 != dis11;
constraint dis4 != dis11;
constraint dis4 != dis12;
constraint dis4 != dis5;
constraint dis11 != dis12;

solve satisfy;
output ["dis3 = \(dis3)\t dis4 = \(dis4)\t dis5 = \(dis5)\n",
        "dis11 = \(dis11)\t dis12 = \(dis12)"];
