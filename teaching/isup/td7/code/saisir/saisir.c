#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saisir.h"

void saisir_chaine(char* s, int size_max) {
  fgets(s, size_max, stdin);
  // On enlève le retour à la ligne si la chaîne termine par celui-ci.
  // La fonction `strlen` calcule la longueur de la chaine de caractère (parcourt le tableau jusqu'au caractère de fin '\0').
  int size = strlen(s);
  if (s[size-1] == '\n') {
    s[size-1] = '\0';
  }
  // Sinon il peut rester des éléments dans le buffer d'input après la taille maximale.
  else {
    vider_buffer_input();
  }
}

void vider_buffer_input() {
  // On lit caractères par caractères jusqu'à ce qu'on arrive à un '\n'.
  // Ce qu'on enlève est l'excédent de l'utilisateur: ce qu'on a pas pu stocker dans le tableau "prenom".
  char c = getchar();
  while(c != '\n' && c != EOF) {
    c = getchar();
  }
}

