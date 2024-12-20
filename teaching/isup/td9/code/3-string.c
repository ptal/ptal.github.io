#include <stdio.h>
#include <stdlib.h>

int occurrence(char* string, char letter) {
  int n = 0;
  for(int i = 0; string[i] != '\0'; i++) {
    if (string[i] == letter) {
      n = n + 1;
    }
  }
  return n;
}

int length(char* string) {
  int l = 0;
  for(; string[l] != '\0'; l++){}
  return l;
}

int longueurEnTete(char* string, char letter) {
  int i = 0;
  for(; string[i] != '\0' && string[i] == letter; i++) {}
  return i;
}

int longueurEnQueue(char* string, char letter) {
  int l = 0;
  for(int i=0; string[i] != '\0'; i++) {
    if(string[i] == letter) {
      l = l + 1;
    }
    else {
      l = 0;
    }
  }
  return l;
}

// Retourne 0 si les mots sont différents et 1 si ils sont égaux.
int egalMot(char* s1, char* s2) {
  if(s1[0] == s2[0]) {
    if(s1[0] == '\0') {
      return 1;
    }
    else {
      return egalMot(&s1[1], &s2[1]);
    }
  }
  else {
    return 0;
  }
}

int egalMotIteratif(char* s1, char* s2) {
  int i;
  for(i = 0; s1[i] != '\0' && s1[i] == s2[i]; i++) {}
  return s1[i] == s2[i] && s1[i] == '\0';
}

char* renverse(char* string) {
  int l = length(string);
  char* reversed = malloc((l+1) * sizeof(char));
  for(int i=0; i < l; i++) {
    reversed[i] = string[l-i-1];
  }
  reversed[l] = '\0';
  return reversed;
}

int palindrome(char* string) {
  int l = length(string);
  for(int i=0; i < l/2; i++) {
    if(string[i] != string[l-i-1]) {
      return 0;
    }
  }
  return 1;
}

int palindrome2(char* string) {
  char* reversed = renverse(string);
  int result = egalMot(reversed, string);
  free(reversed);
  return result;
}

int main() {
  char* string = "abcaabba";
  printf("%d (expecting 4)\n", occurrence(string, 'a'));
  printf("%d (expecting 8)\n", length(string));
  printf("%d (expecting 1)\n", longueurEnTete(string, 'a'));
  printf("%d (expecting 0)\n", longueurEnTete(string, 'b'));
  printf("%d (expecting 2)\n", longueurEnTete("ccb", 'c'));
  printf("%d (expecting 1)\n", longueurEnQueue(string, 'a'));
  printf("%d (expecting 0)\n", longueurEnQueue(string, 'b'));
  printf("%d (expecting 2)\n", longueurEnQueue("aaabcccbbcc", 'c'));
  printf("%d (expecting 2)\n", longueurEnQueue("cc", 'c'));
  printf("%d (expecting 1)\n", egalMot(string, string));
  printf("%d (expecting 0)\n", egalMot("a", "aa"));
  printf("%d (expecting 0)\n", egalMot("ba", "aa"));
  printf("%d (expecting 1)\n", egalMotIteratif(string, string));
  printf("%d (expecting 0)\n", egalMotIteratif("a", "aa"));
  printf("%d (expecting 0)\n", egalMotIteratif("ba", "aa"));
  char* result = renverse(string);
  printf("%s (expecting abbaacba)\n", result);
  free(result);
  result = renverse("a");
  printf("%s (expecting a)\n", result);
  free(result);
  printf("%d (expecting 0)\n", palindrome(string));
  printf("%d (expecting 1)\n", palindrome("abccba"));
  printf("%d (expecting 1)\n", palindrome("a"));
  return 0;
}
