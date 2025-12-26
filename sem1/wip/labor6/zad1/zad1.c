#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int *arr, int n) {
  for(int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

bool nextPermutation(int *arr, int n, int min, int max) {
  int j;
  for(int i = n - 1; i >= 0; i--)
    if(arr[i]++ < max) {
      for(j = i + 1; j < n; j++)
        arr[j] = min;

      return true;
    }
  
  return false;
}

bool isValid(int *arr, int n) {
  int *row   = (int *)calloc(n + 1, sizeof(int));
  int *dgnl1 = (int *)calloc(2 * n, sizeof(int));
  int *dgnl2 = (int *)calloc(2 * n, sizeof(int));

  if(row == NULL || dgnl1 == NULL || dgnl2 == NULL) {
    perror("Memory allocation error");
    free(row);
    free(dgnl1);
    free(dgnl2);
    return false;
  }

  for(int i = 0; i < n; i++) 
    if(++row[arr[i]]           > 1 || 
       ++dgnl1[i - arr[i] + n] > 1 || 
       ++dgnl2[i + arr[i]]     > 1)
      return false;

  free(row);
  free(dgnl1);
  free(dgnl2);
  return true;
}

int main(int argc, char *argv[]) { 
  if(argc != 2) {
    printf("Unknown usage\n");
    return 1;
  }

  int n = atoi(argv[1]);

  int *arr = (int *)malloc(n * sizeof(int));
  if(arr == NULL) {
    perror("Memory allocation error");
    free(arr);
    return 1;
  }

  for(int i = 0; i < n; i++)
    arr[i] = 1;
  
  int validSolutions = 0;

  do {
    if(isValid(arr, n)) {
      printArray(arr, n);
      validSolutions++;
    }
  } while(nextPermutation(arr, n, 1, n));

  printf("Number of solutions: %d\n", validSolutions);

  free(arr);
  return 0;
}