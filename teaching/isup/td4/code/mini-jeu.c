#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int ask_user_integer(char* what) {
  int x;
  printf("Entrer votre %s : ", what);
  scanf("%d", &x);
  return x;
}

int generate_number() {
  return rand() % MAX;
}

// Return the result of the game
//   * `-1` if the guess is lower than the expected number,
//   * `0` if equal, and
//   * `1` if greater.
int compare_number(int expected, int guessed) {
  if(guessed < expected) {
    return -1;
  }
  else if(guessed > expected) {
    return 1;
  }
  return 0;
}

// Return 1 if he won, 0 otherwise.
int has_won(int game_result) {
  if(game_result == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

void print_choice_msg(int result) {
  if (result == -1) {
    printf("Votre nombre est inférieur au nombre attendu.\n");
  }
  else if (result == 1) {
    printf("Votre nombre est supérieur au nombre attendu.\n");
  }
  else {
    printf("Vous avez gagné, félicitation !\n");
  }
}

int process_choice(int expected, int user) {
  int result = compare_number(expected, user);
  print_choice_msg(result);
  return result;
}

// The main loop putting all the functions together.
void process_loop() {
  int result = -1;
  int expected = generate_number();
  while(!has_won(result)) {
    int user = ask_user_integer("choix");
    result = process_choice(expected, user);
  }
}

void welcome_msg() {
  printf("Bienvenue sur WonderGuess.\n\n");
}

void exit_msg() {
  printf("\nOn espère vous revoir bientôt.\n");
}

int main() {
  // Initialize to a different seed each time the program is launched.
  // Hence, the numbers generated are not always the same.
  srand(time(NULL));
  welcome_msg();
  process_loop();
  exit_msg();
  return 0;
}
