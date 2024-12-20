#include <stdio.h>
#include <stdlib.h>

// On choisit une représentation dans le tas car c'est un tableau dynamique, et si un utilisateur utilise notre tableau, on ne sait pas forcément ce qu'il va choisir comme taille à l'avance.
// Notez que les VLA ne peuvent pas être utilisée non plus car on veut pouvoir retourner notre tableau des fonctions.

struct Matrix {
  int size;
  int** data;
};
typedef struct Matrix Matrix;

Matrix init_matrix(int n) {
  Matrix m;
  m.size = n;
  m.data = malloc(n * sizeof(int*));
  for(int i =0; i < n; i++) {
    m.data[i] = malloc(n * sizeof(int));
  }
  return m;
}

void free_matrix(Matrix m) {
  for(int i = 0; i < m.size; i++) {
    free(m.data[i]);
  }
  free(m.data);
}

Matrix build_mult_table_modulo(int n) {
  Matrix m = init_matrix(n);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      m.data[i][j] = (i * j) % n;
    }
  }
  return m;
}

void print_table_modulo(Matrix m) {
  printf("* | ");
  for(int k = 0; k < m.size; k++) {
    printf("%d ", k);
  }
  printf("\n");
  for(int i = 0; i < m.size; i++) {
    printf("%d | ", i);
    for(int j = 0; j < m.size; j++) {
      printf("%d ", m.data[i][j]);
    }
    printf("\n");
  }
}

int main() {
  Matrix m = build_mult_table_modulo(3);
  print_table_modulo(m);
  free_matrix(m);
  return 0;
}
