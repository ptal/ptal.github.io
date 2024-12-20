#include <stdio.h>
#include <stdlib.h>

int prod_chi(int n) {
  int result = n % 10;
  n = n / 10;
  while(n > 0) {
    result = result * (n % 10);
    n = n / 10;
  }
  return result;
}

int main() {
  printf("%d %d %d %d \n", prod_chi(0), prod_chi(1), prod_chi(2), prod_chi(3));
  printf("%d\n", prod_chi(251));
  printf("%d", prod_chi(2513));
  return 0;
}
