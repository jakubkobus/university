#include <stdio.h>
#include <stdlib.h>

#define GUESS_SIZE 4
#define GUESS_MIN  1
#define GUESS_MAX  6

typedef struct {
  int hits;
  int misplaced;
} CompareResult;

CompareResult compare(int *correct, int *guess) {
  int hits = 0, misplaced = 0;
  int correctLeft[GUESS_SIZE], guessLeft[GUESS_SIZE];
  int used[GUESS_SIZE] = { 0 };
  int countLeft = 0;

  for(int i = 0; i < GUESS_SIZE; i++)
    if(correct[i] == guess[i])
      hits++;
    else {
      correctLeft[countLeft] = correct[i];
      guessLeft[countLeft++] = guess[i];
    }

  for(int i = 0; i < countLeft; i++)
    for(int j = 0; j < countLeft; j++)
      if(!used[j] && guessLeft[i] == correctLeft[j]) {
        misplaced++;
        used[j] = 1;
        break;
      }

  return (CompareResult){ hits, misplaced };
}

void generateAllCombinations(int ***allCombinations, int *total) {
  int range = GUESS_MAX - GUESS_MIN + 1;
  int totalCombinations = 1;
  int i, j, k, l;

  for(i = 0; i < GUESS_SIZE; i++)
    totalCombinations *= range;

  *allCombinations = malloc(totalCombinations * sizeof(int *));
  for(i = 0; i < totalCombinations; i++)
    (*allCombinations)[i] = malloc(GUESS_SIZE * sizeof(int));

  int count = 0;
  for(i = GUESS_MIN; i <= GUESS_MAX; i++)
    for(j = GUESS_MIN; j <= GUESS_MAX; j++)
      for(k = GUESS_MIN; k <= GUESS_MAX; k++)
        for(l = GUESS_MIN; l <= GUESS_MAX; l++) {
          (*allCombinations)[count][0] = i;
          (*allCombinations)[count][1] = j;
          (*allCombinations)[count][2] = k;
          (*allCombinations)[count++][3] = l;
        }

  *total = totalCombinations;
}

int main() {
  int **allCombinations;
  int totalCombinations;
  int guess[GUESS_SIZE];
  int hits = 0, attempt = 1, misplaced;

  generateAllCombinations(&allCombinations, &totalCombinations);

  for(int i = 0; i < GUESS_SIZE; i++)
    guess[i] = GUESS_MIN;

  while(hits != GUESS_SIZE) {
    printf("%d: ", attempt++);
    for(int i = 0; i < GUESS_SIZE; i++)
      printf("%d ", guess[i]);
    printf("?\n");

    printf("Na swoim miejscu: ");
    scanf("%d", &hits);
    printf("Nie na swoim miejscu: ");
    scanf("%d", &misplaced);

    int **validCombinations = malloc(totalCombinations * sizeof(int *));
    int newTotalCombinations = 0;

    for(int i = 0; i < totalCombinations; i++)
      if(allCombinations[i] != NULL) {
        CompareResult result = compare(allCombinations[i], guess);
        if(result.hits == hits && result.misplaced == misplaced)
          validCombinations[newTotalCombinations++] = allCombinations[i];
        else
          free(allCombinations[i]);
      }

    free(allCombinations);
    allCombinations = validCombinations;
    totalCombinations = newTotalCombinations;

    if(totalCombinations == 0) {
      printf("Oszukujesz!\n");
      break;
    }

    for(int i = 0; i < GUESS_SIZE; i++)
      guess[i] = allCombinations[0][i];
  }

  if(hits == GUESS_SIZE && totalCombinations != 0)
    printf("Wygralem!\n");

  for(int i = 0; i < totalCombinations; i++)
    free(allCombinations[i]);
  free(allCombinations);

  return 0;
}
