int: n;
int: max_cost;

set of int: N = 1..n;

array[N] of int: cost;
array[N] of int: value;

array[N] of var bool: taken;

var int: bag_cost = sum(i in N where taken[i])
                       (cost[i]);

constraint bag_cost < max_cost;

var int: obj = sum(i in N where taken[i])(value[i]);

solve maximize obj;

output [ "Total Cost = \(bag_cost)\n",
         "Total Value = \(obj)\n"] ++
        ["Objects cost  = "] ++ [show_int(3, cost[i]) | i in N] ++ ["\n"] ++
        ["Objects value = "] ++ [show_int(3, value[i]) | i in N] ++ ["\n"] ++
        ["Objects taken = "] ++ [show_int(3, taken[i]) | i in N] ++ ["\n"];
