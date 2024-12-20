#include <stdio.h>
#include <stdlib.h>

struct String {
  char c;
  struct String* next;
};
typedef struct String String;

String* init_from_str(char* string) {
  if(string[0] == '\0') {
    return NULL;
  }
  String* head = malloc(sizeof(String));
  head->c = string[0];
  String* current = head;
  for(int i=1; string[i] != '\0'; i++) {
    current->next = malloc(sizeof(String));
    current = current->next;
    current->c = string[i];
  }
  return head;
}

void free_string(String* s) {
  while(s != NULL) {
    String* tmp = s;
    s = s->next;
    free(tmp);
  }
}

void print_string(String* s) {
  for(String* current = s; current != NULL; current = current->next) {
    printf("%c",current->c);
  }
}

String* push_back(String* head, char letter) {
  // On crée notre nouvel élément.
  String* extended = malloc(sizeof(String));
  extended->c = letter;
  extended->next = NULL;

  // On place l'élément à la fin de `head` sauf head est vide.
  if(head == NULL) {
    return extended;
  }
  else {
    String* last = head;
    while(last->next != NULL){
      last = last->next;
    }
    last->next = extended;
    return head;
  }
}

// Les exercices commencent ici.

int occurrence(String* string, char letter) {
  if(string == NULL) { return 0; }
  int n = 0;
  for(String* current = string; current != NULL; current = current->next) {
    if (current->c == letter) {
      n = n + 1;
    }
  }
  return n;
}

int length(String* string) {
  int l = 0;
  for(String* current = string; current != NULL; current = current->next) {
    l++;
  }
  return l;
}

int longueurEnTete(String* string, char letter) {
  int i = 0;
  for(String* current = string;
      current != NULL && current->c == letter;
      current = current->next) {
    i = i + 1;
  }
  return i;
}

int longueurEnQueue(String* string, char letter) {
  int l = 0;
  for(String* current = string; current != NULL; current = current->next) {
    if(current->c == letter) {
      l = l + 1;
    }
    else {
      l = 0;
    }
  }
  return l;
}

// Retourne 0 si les mots sont différents et 1 si ils sont égaux.
int egalMot(String* s1, String* s2) {
  if(s1 == s2) { // Par exemple si vous appelez egalMot(NULL, NULL) mais aussi egalMot(s, s)
    return 1;
  }
  // Si on atteint la fin d'un des mots.
  else if(s1 == NULL || s2 == NULL) {
    return 0;
  }
  else if(s1->c == s2->c) {
    return egalMot(s1->next, s2->next);
  }
  else {
    return 0;
  }
}

int egalMotIteratif(String* s1, String* s2) {
  while(s1 != NULL && s2 != NULL && s1->c == s2->c) {
    s1 = s1->next;
    s2 = s2->next;
  }
  return s1 == s2;
}

String* renverse(String* string) {
  if(string == NULL) {
    return NULL;
  }
  // On renverse d'abord le reste de la chaine.
  String* reversed = renverse(string->next);

  // On l'ajoute à la fin de la chaine renversée.
  return push_back(reversed, string->c);
}

// Cette fonction permet de détecter un palindrome dans une liste simplement chainée en O(n).
// Quand on arrive à "la fin de la récursion", la variable `mirror` représente l'élément mirroir à l'élément courant `string`.
// Quand on remonte de la récursion, on fait avancer mirroir pour correspondre au mirroir du prochain élément.
// NOTE : une technique similaire pourrait être utilisée avec `renverse` pour qu'il soit on O(n) au lieu de O(n^2).
int palindrome_aux(String** mirror, String* string) {
  if(string == NULL) {
    return 1;
  }
  else {
    int result = palindrome_aux(mirror, string->next);
    if(result == 0) {
      return 0;
    }
    else {
      if(string->c == (*mirror)->c) {
        *mirror = (*mirror)->next;
        return 1;
      }
      else {
        return 0;
      }
    }
  }
}

int palindrome(String* string) {
  String* head = string;
  return palindrome_aux(&head, string);
}

int palindrome2(String* string) {
  String* reversed = renverse(string);
  int result = egalMot(reversed, string);
  free_string(reversed);
  return result;
}

int main() {
  String* string = init_from_str("abcaabba");
  String* string2 = init_from_str("abcaabba");
  String* ccb = init_from_str("ccb");
  String* aaabcccbbcc = init_from_str("aaabcccbbcc");
  String* cc = init_from_str("cc");
  String* palin = init_from_str("abccba");
  String* almost_palin = init_from_str("abbcba");
  String* singleton = init_from_str("a");
  printf("%d (expecting 4)\n", occurrence(string, 'a'));
  printf("%d (expecting 8)\n", length(string));
  printf("%d (expecting 1)\n", longueurEnTete(string, 'a'));
  printf("%d (expecting 0)\n", longueurEnTete(string, 'b'));
  printf("%d (expecting 2)\n", longueurEnTete(ccb, 'c'));
  printf("%d (expecting 1)\n", longueurEnQueue(string, 'a'));
  printf("%d (expecting 0)\n", longueurEnQueue(string, 'b'));
  printf("%d (expecting 2)\n", longueurEnQueue(aaabcccbbcc, 'c'));
  printf("%d (expecting 2)\n", longueurEnQueue(cc, 'c'));
  printf("%d (expecting 1)\n", egalMot(string, string));
  printf("%d (expecting 1)\n", egalMot(string, string2));
  printf("%d (expecting 0)\n", egalMot(cc, ccb));
  printf("%d (expecting 0)\n", egalMot(NULL, cc));
  printf("%d (expecting 1)\n", egalMot(NULL, NULL));
  printf("%d (expecting 1)\n", egalMotIteratif(string, string));
  printf("%d (expecting 1)\n", egalMotIteratif(string, string2));
  printf("%d (expecting 0)\n", egalMotIteratif(cc, ccb));
  printf("%d (expecting 0)\n", egalMotIteratif(NULL, cc));
  printf("%d (expecting 1)\n", egalMotIteratif(NULL, NULL));
  String* result = renverse(string);
  print_string(result);
  printf(" (expecting abbaacba)\n");
  free_string(result);
  result = renverse(cc);
  print_string(result);
  printf(" (expecting cc)\n");
  free_string(result);
  printf("%d (expecting 0)\n", palindrome(string));
  printf("%d (expecting 1)\n", palindrome(palin));
  printf("%d (expecting 0)\n", palindrome(almost_palin));
  printf("%d (expecting 1)\n", palindrome(singleton));
  free_string(string);
  free_string(string2);
  free_string(ccb);
  free_string(aaabcccbbcc);
  free_string(cc);
  free_string(singleton);
  free_string(palin);
  free_string(almost_palin);
  return 0;
}
