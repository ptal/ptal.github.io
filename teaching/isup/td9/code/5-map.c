#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

struct liste {
  int val;
  struct liste* suivant;
};
typedef struct liste liste;

#define VAL(list) ((list)->val)
#define RESTE(list) ((list)->suivant)

liste* cons(int x, liste* l) {
  liste* head = malloc(sizeof(liste));
  head->val = x;
  head->suivant = l;
  return head;
}

void print_liste(liste* l) {
  for(liste* current = l; current != NULL; current = RESTE(current)) {
    printf("%d ", VAL(current));
  }
}

liste* map(liste* l, int (*f)(int)) {
  if (l == NULL) return l;
  else return cons(f(VAL(l)), map(RESTE(l), f));
}

int mul_2(int x) {
  return x * 2;
}

jmp_buf map2_ctx;

liste* map2(liste* l, int (*f)(int), int (*test)(int)) {
  if (l == NULL) return l;
  else {
    if(test(VAL(l))) {
      return cons(f(VAL(l)), map2(RESTE(l), f, test));
    }
    else {
      longjmp(map2_ctx, 1);
    }
  }
}

liste* map1(liste* l, int (*f)(int), int (*test)(int)) {
  short exception = setjmp(map2_ctx);
  if(exception == 0) {
    return map2(l, f, test);
  }
  else {
    printf("\n\nErreur lancée dans la fonction map !");
    exit(1);
  }
}

int fail_on_3(int x) {
  return x != 3;
}

int main() {
  liste* l1 = cons(1, cons(2, cons(3, NULL)));
  printf("l1: ");
  print_liste(l1);
  liste* l2 = map(l1, mul_2);
  printf("\nl2: ");
  print_liste(l2);
  liste* l3 = map1(l2, mul_2, fail_on_3); // It should not fail.
  printf("\nl3: ");
  print_liste(l3);
  liste* l4 = map1(l1, mul_2, fail_on_3); // It should fail, and not print the list "l4".
  printf("\nl4: ");
  print_liste(l4);
  return 0;
}
