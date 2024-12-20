var 0..100: men;
var 0..100: women;
var 0..100: children;

constraint men + women + children = 100;
constraint 6*men + 4 * women + children = 200;
constraint women = 5 * men;

solve satisfy;

output ["men = ",show(men),";\nwomen = ",show(women),";\nchildren = ",show(children),";\n"];
