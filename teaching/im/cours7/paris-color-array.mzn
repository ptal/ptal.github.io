int: nc = 3;
int: na = 5;

% Les indices des différents arrondissements dans le tableau `color`.
int: arr3 = 1;
int: arr4 = 2;
int: arr5 = 3;
int: arr11 = 4;
int: arr12 = 5;

set of int: ARR = 1..5;
set of int: COLOR = 1..nc;
set of int: PRICE = {1, 4};

array[ARR] of var COLOR: color;
array[COLOR] of PRICE: price = [1, 1, 4];

constraint color[arr3] != color[arr4];
constraint color[arr3] != color[arr11];
constraint color[arr4] != color[arr11];
constraint color[arr4] != color[arr12];
constraint color[arr4] != color[arr5];
constraint color[arr11] != color[arr12];

% array[ARR] of var PRICE: arr_price = [price[color[arr]] | arr in ARR];

var 1..5*4: obj = sum(arr in ARR)
                     (price[color[arr]]);

solve minimize obj;

output ["Minimum price:\(obj)\n",
        "Colors: \(color)\n"];
