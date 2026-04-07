#include <stdio.h>
#include <vector>

#include "sort/result.hpp"
#include "sort/hybrid.hpp"

int main() {
  int n;
  scanf("%d", &n);

  std::vector<int> arr(n);
  for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);

  std::vector<int> arrCopy = arr;

  if (n < 40) {
    printf("Original array:\n");
    util::printArray(arr);
  }

  Result s = hybridSort(arr, 0, n - 1);

  if (n < 40) {
    printf("Original array:\n");
    util::printArray(arrCopy);
    printf("Sorted array:\n");
    util::printArray(arr);
  }

  printf("Sorted: %s\n", s.sorted ? "true" : "false");
  printf("Comparisons: %d\n", s.comparisons);
  printf("Swaps: %d\n", s.swaps);
}
