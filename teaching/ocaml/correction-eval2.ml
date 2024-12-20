type int_list = Empty | Value of int * int_list
let rec concat l1 l2 =
  match l1 with
  | Empty -> l2
  | Value(x, l) -> Value(x, concat l l2)

let rec insert x l =
  match l with
  | Value(y, l') when x < y -> Value(x, Value(y, l'))
  | Value(y, l') -> Value(y, ins x l')
  | Empty -> Value(x, Empty)

let rec sort = function
  | Empty -> Empty
  | Value (x, l) -> insert x (sort l)

(* Complexité en O(n^2)  (n carré) *)

type utilisateur =
  {
    nom: string;
    amis: string list;
  }

type cible =
  | Public
  | Amis
  | Groupe of string list

type publication =
  {
    auteur: string;
    message: string;
    cible: cible;
  }

let utilisateur ~nom amis = {nom; amis}
let publication ?(cible = Amis) ~auteur message =
  {auteur; message; cible}

let afficher_publication {auteur; message; cible=_} =
  print_endline (auteur ^ ": " ^ message)

let acces_autorise {nom; amis} publication =
  nom = publication.auteur ||
  match publication.cible with
  | Public -> true
  | Amis -> List.mem publication.auteur amis
  | Groupe groupe -> List.mem nom groupe

let filtre_publications utilisateur publications =
  List.filter
    (acces_autorise utilisateur)
    publications

let categoriser publications =
  let rec aux acc_pub acc_priv l =
    match l with
    | [] -> List.rev acc_pub, List.rev acc_priv
    | ({cible = Public; _} as publication) :: tail ->
      aux (publication :: acc_pub) acc_priv tail
    | ({cible = (Amis | Groupe _); _} as publication)
      :: tail ->
      aux acc_pub (publication :: acc_priv) tail
  in
  aux [] [] publications