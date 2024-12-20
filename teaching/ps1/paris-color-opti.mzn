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

var 1..nc*5: cost = dis3 + dis4 + dis5 + dis11 + dis12;

solve minimize cost;

output ["Printing cost = \(cost)\n",
        "dis3 = \(dis3)\t dis4 = \(dis4)\t dis5 = \(dis5)\n",
        "dis11 = \(dis11)\t dis12 = \(dis12)"];
