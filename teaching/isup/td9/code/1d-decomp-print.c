#include <stdio.h>
#include <stdlib.h>

struct Array {
  int size;
  int* data;
};
typedef struct Array Array;

Array empty() {
  Array array;
  array.size = 0;
  array.data = NULL;
  return array;
}

void free_array(Array array) {
  free(array.data);
}

Array extend_with(Array from, int e) {
  Array array;
  array.size = from.size + 1;
  array.data = malloc(array.size * sizeof(int));
  for(int i=0; i < from.size; i++){
    array.data[i] = from.data[i];
  }
  array.data[array.size - 1] = e;
  free_array(from);
  return array;
}

Array decomp(int n, int b) {
  if(n == 0) {
    return empty();
  }
  else {
    int a = n % b;
    Array result = decomp(n / b, b);
    return extend_with(result, a);
  }
}

void print_array(Array result) {
  for(int i=0; i < result.size; i++) {
    printf("%d ", result.data[i]);
  }
}

int main() {
  printf("Entrez votre nombre et base:");
  int n;
  int b;
  scanf("%d %d", &n, &b);
  Array result = decomp(n, b);
  print_array(result);
  free_array(result);
  return 0;
}
