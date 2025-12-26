#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int *arr, int n) {
  for(int i = 0; i < n; i++)
    printf("%d ", arr[i] + 1);
  printf("\n");
}

void USTAW(int i, int *position, int n, bool *bije_wiersz, bool *bije_przek1, bool *bije_przek2, int *sol) {
  for(int j = 0; j < n; j++) {
    if(!(bije_wiersz[j] || bije_przek1[i + j] || bije_przek2[i - j + n])) {
      position[i] = j;
      bije_wiersz[j] = bije_przek1[i + j] = bije_przek2[i - j + n] = true;

      if(i < n - 1)
        USTAW(i + 1, position, n, bije_wiersz, bije_przek1, bije_przek2, sol);
      else {
        printArray(position, n);
        (*sol)++;
      }

      position[i] = 0;
      bije_wiersz[j] = bije_przek1[i + j] = bije_przek2[i - j + n] = false;
    }
  }
}

void HETMAN(int n) {
  int *position = (int *)calloc(n, sizeof(int));
  bool *bije_wiersz = (bool *)calloc(n, sizeof(bool));
  bool *bije_przek1 = (bool *)calloc(2 * n, sizeof(bool));
  bool *bije_przek2 = (bool *)calloc(2 * n, sizeof(bool));

  if(position == NULL || bije_wiersz == NULL || 
     bije_przek1 == NULL || bije_przek2 == NULL) {
    perror("Memory allocation error");
    free(position);
    free(bije_wiersz);
    free(bije_przek1);
    free(bije_przek2);
    return;
  }

  int solutions = 0;  
  USTAW(0, position, n, bije_wiersz, bije_przek1, bije_przek2, &solutions);
  printf("Number of solutions: %d\n", solutions);
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Unknown usage\n");
    return 1;
  }

  int n = atoi(argv[1]);
  HETMAN(n);

  return 0;
}