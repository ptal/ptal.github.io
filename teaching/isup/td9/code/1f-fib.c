#include <stdio.h>
#include <stdlib.h>

// Le problème avec la version de l'exercice 1e, est qu'on recalcule plusieurs fois les mêmes éléments.
// En effet, pour fib(n-1) et fib(n-2), l'appel a fib(n-1) va également recalculer fib(n-2).
// La version itérative n'a pas ce problème puisque les appels intermédiaires sont sauvegardés.

int fib(int n) {
  int a = 1;
  int b = 1;
  for(int i = 1; i < n; i++) {
    int tmp = a;
    a = a + b;
    b = tmp;
  }
  return a;
}

int main() {
  printf("%d %d %d %d", fib(0), fib(1), fib(2), fib(10));
  return 0;
}
