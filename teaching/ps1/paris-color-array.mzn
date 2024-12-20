int: nc = 3;
int: na = 5;

% Indices of the districts in the array `color`.
int: dis3 = 1;
int: dis4 = 2;
int: dis5 = 3;
int: dis11 = 4;
int: dis12 = 5;

set of int: DIS = 1..5;
set of int: COLOR = 1..nc;
set of int: PRICE = {1, 4};

array[DIS] of var COLOR: color;
array[COLOR] of PRICE: price = [1, 1, 4];

constraint color[dis3] != color[dis4];
constraint color[dis3] != color[dis11];
constraint color[dis4] != color[dis11];
constraint color[dis4] != color[dis12];
constraint color[dis4] != color[dis5];
constraint color[dis11] != color[dis12];

array[DIS] of var PRICE: price_of_dis = [price[color[dis]] | dis in DIS];

var 1..5*4: obj = sum(price_of_dis);

solve minimize obj;

output ["Minimum price: \(obj)\n",
        "Colors: \(color)\n",
        "Prices: \(price_of_dis)\n"];
