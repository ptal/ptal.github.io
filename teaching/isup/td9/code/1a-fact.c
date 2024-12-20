#include <stdio.h>
#include <stdlib.h>

int fact(int n) {
  static int largest_result = 1;
  static int largest_n = 1;

  int result = 1;
  int i = 1;
  // On récupère les résultats sauvegardé des appels précédents si besoin.
  if(n > largest_n) {
    i = largest_n+1; // On initialise 'i' au prochain car on a déjà calculé "n".
    result = largest_result;
  }
  // Calcule de la factorielle.
  for( ; i <= n; i++) {
    result = result * i;
  }
  // Enregistrement du plus grand résultat si on a calculé un nombre plus grand.
  if (largest_n < n) {
    largest_n = n;
    largest_result = result;
  }
  return result;
}

int main() {
  printf("%d %d %d %d \n", fact(0), fact(1), fact(2), fact(3));
  printf("%d", fact(10));
  return 0;
}
