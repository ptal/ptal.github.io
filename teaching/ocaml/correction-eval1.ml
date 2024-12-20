(* Exo 1 *)
2 + 40 : int
(if ((2. -. 1.):float > 2.):bool then "yo" else "oy"): string
if ((x:string) = "entier"):bool then 1:int else 1.:float ---> erreur de typage: int et float ne peuvent pas être unifié dans un type commun
(fun (x:string) (f: string -> string) -> ((f (x ^ ".txt"):string):string) ^ "\n"): string -> (string -> string) -> string
let x = (fun f -> (f:((int->int->int)->int->'a) (+):(int->int->int) 4):'a): ((int->int->int)->int->'a) -> 'a

(* Exo 2 *)
let a = 42: int
let f x = a + x: int -> int
let g a = f a: int -> int
let h () = g a: unit -> int
let a = 1 : int
let i f = g a + f (g a) : (int -> int) -> int
let b = i g + a + g (h()) + f a : int

(* Exo 3 *)
let f : int -> int=
  let a = 42 in
  let f x = a + x in
    f

let g a : 'a -> int = f 23

let h () : unit -> int=
  let a = 9 in
    g a

let a:int = 1 ;;

let i f : (int -> int) -> int  =
   let g z = f 2 in
     g a + f (g a)

let b = i g + a + g (h()) + f a

  i g -->
       --> g 2 + g (f 2)
       --> f 23 + f 23
       --> 65 + 65
       --> 130

  a = 1

  g (h()) --> g ( f 23)
             --> f 23
             --> 65

   f a --> f 1 --> 43

  result = 44+65+1+65+43 = 218

(* solution demandee - en supposant que n >= 0 *)
let rec odd n =
  if n = 0 then false else even (pred n)
and even n =
  if n = 0 then true  else odd  (pred n);;
(* ou *)
let rec even n = n = 0 || odd (pred n)
and odd      n = n = 1 || not (even n);;
(* pour prendre en compte les nombres negatifs : *)
let odd n = if n >= 0 then odd n else odd (-n)
and even n = if n >= 0 then even n else even (-n)
