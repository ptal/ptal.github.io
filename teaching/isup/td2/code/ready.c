#include <stdio.h>

// Les clauses define permettent de donner un nom à des constantes.
// En pratique, c'est comme si vous substituez `MAX_AGE` partout dans le code par `200`.
#define MAX_AGE 130

int main(int argc, char* args[]) {
  // On peut afficher du texte avec `printf` et \n est utile pour revenir à la ligne.
  printf("Bonjour !\n");
  printf("T'as quel âge ? ");

  // On déclare une variable de type entier (int) et on attends que l'utilisateur tape quelque chose au clavier.
  int age;
  // Le symbole `%d` dans `scanf` indique qu'on attend que l'utilisateur tape un entier.
  // Attention, il faut faire très attention à passer l'adresse de la variable à `scanf` avec `&` devant son nom.
  scanf("%d", &age);

  // Si l'utilisateur tape un âge invalide, il faut lui redemander.
  // Notez qu'on utilise une boucle `while` pour répéter l'action.
  // Le `||` signifie OU, et dans ce cas, on accepte que des âges (donc pas de négatif ou d'âge supérieur à MAX_AGE).
  while (age < 0 || age > MAX_AGE) {
    printf("Tu délires mon pote ! Essaye encore pour voir: ");
    scanf("%d", &age);
  }

  // On compare son âge et affiche un message.
  if (age < 18) {
    printf("C'est beau la jeunesse...\n");
  }
  // Le `&&` signifie ET, dans ce cas, on veut que l'âge soit compris entre 18 ET 29 ans.
  // Notez le `%d` dans le `printf`, c'est pareil que dans le `scanf` sauf que ici on affiche
  // la variable `age` sur l'écran. Il faut absolument qu'une variable entière suive le message du `printf`.
  else if (age >= 18 && age < 29) {
    printf("Oui c'est bien %d ans !\n", age);
  }
  else {
    printf("Mauvaise pente...\n");
  }

  printf("A++\n");
  return 0;
}
