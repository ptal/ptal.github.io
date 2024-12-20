#include <stdio.h>

// Il est toujours préférable de nommer les constantes au lieu de laisser trainer des chiffres seuls dans le programme.
#define NUM_NOTES 5
#define NAME_LEN_MAX 50

int main() {
  printf("Bienvenue sur notre fabuleux programme de prise de notes.\n");
  printf("Quel est ton nom ? ");

  // On peut déclarer un tableau de caractères comme n'importe quel autre tableau.
  // Par contre, une chaine de caractères est toujours terminée par le caractère `\0`.
  char name[NAME_LEN_MAX];
  // On utilise par `scanf` ici car `scanf` peut laisser l'utilisateur rentrer plus de caractères que ce que le tableau peut en contenir, ce qui fait qu'on pourrait aller écrire dans la mémoire d'autres variables.
  // `fgets` permet de récupérer une ligne de l'entrée standard `stdin` avec au maximum `sizeof(name)` caractères.
  // `fgets` termine automatiquement la chaine de caractères avec `\0`.
  fgets(name, sizeof(name), stdin);
  // `%s` permet d'afficher la chaine de caractères jusqu'au `\0` final.
  printf("Hello %s\n", name);

  // Pareil que pour les caractères, on déclare un tableau de `int` de cette manière.
  // Avec `{ 0 }` on initialise le tableau à zéro, par exemple avec :
  //    int notes[NUM_NOTES] = { 1, 2, 3, 4, 5 };
  // on initialise chaque case du tableau avec les valeurs correspondantes.
  int notes[NUM_NOTES] = { 0 };
  printf("Insère une série de %d notes: ", NUM_NOTES);
  for(int i = 0; i < NUM_NOTES; i++) {
    // Ne pas oublier de donner à `scanf` l'adresse mémoire de la case du tableau.
    scanf("%d", &notes[i]);
  }

  int sum = 0;
  for(int i = 0; i <NUM_NOTES; i++) {
    sum += notes[i];
  }
  int average = sum / NUM_NOTES;
  printf("Ta moyenne est de %d points\n", average);
  return 0;
}