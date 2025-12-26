#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int *getCoins(const char *filename, int *amount) {
  FILE *file = fopen(filename, "r");

  if(file == NULL) {
    fprintf(stderr, "File '%s' does not exist\n", filename);
    return NULL;
  }

  fscanf(file, "%d", amount);
  int *coins = malloc(*amount * sizeof(int));

  int i = 0;
  while(fscanf(file, "%d", &coins[i++]) == 1);
  fclose(file);

  return coins;
}

void solveChangeProblem(int *coins, int n, int r) {
  int *C = malloc((r + 1) * sizeof(int));
  int *D = malloc((r + 1) * sizeof(int));

  if(C == NULL || D == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    return;
  }

  for(int i = 0; i <= r; i++) {
    C[i] = INT_MAX;
    D[i] = -1;
  } C[0] = 0;

  for(int i = 1; i <= r; i++) {
    for(int j = 0; j < n; j++) {
      if(coins[j] <= i && 
         C[i - coins[j]] != INT_MAX &&
         C[i] > C[i - coins[j]] + 1) {
          
        C[i] = C[i - coins[j]] + 1;
        D[i] = coins[j];
      }
    }
  }

  if(C[r] == INT_MAX) {
    printf("%d ==> No solution!\n", r);
  } else {
    printf("%d ==> %d\n", r, C[r]);
    int *result = calloc(n, sizeof(int));
    
    if(result == NULL) {
      printf("Memory allocation error\n");
      return;
    }

    bool found;

    while(r > 0) {
      found = false;

      for(int i = 0; i < n || !found; i++) {
        if(coins[i] == D[r]) {
          result[i]++;
          found = true;
        }
      }

      r -= D[r];
    }

    for(int i = 0; i < n; i++)
      if(result[i] > 0)
        printf("\t%d x %d\n", result[i], coins[i]);

    free(result);
  }

  free(C);
  free(D);
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
    fprintf(stderr, "Unknown usage: <filename:str> <amount:int> ... <amount:int>\n");
    return 1;
  }
  
  int amount;
  int *coins = getCoins(argv[1], &amount);

  if(coins == NULL)
    return 1;

  for(int i = 2; i < argc; i++) {
    if(isdigit(*argv[i]))
      solveChangeProblem(coins, amount, atoi(argv[i]));
    else
      fprintf(stderr, "'%s' is not an integer\n", argv[i]);
  }

  free(coins);
  return 0;
}