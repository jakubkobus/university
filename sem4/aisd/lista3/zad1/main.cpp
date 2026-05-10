#include <vector>
#include <algorithm>
#include <cstdio>

#include "util.hpp"
#include "randomSelect.hpp"
#include "select.hpp"

int main() {
  int n, k;

  if (scanf("%d %d", &n, &k) != 2) {
    fprintf(stderr, "[ERROR] Provide: n k\n");
    return 1;
  }

  std::vector<int> A(n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &A[i]) != 1) {
      fprintf(stderr, "[ERROR] Array element at %d index expected\n", i);
      return 1;
    }
  }

  bool print = (n <= 30);

  std::vector<int> rsA = A;
  std::vector<int> selA = A;
  Stats rsStats;
  Stats selStats;

  if (print) {
    printf("Original array (RANDOMIZED SELECT):\n");
    util::printArray(A, 0, n - 1);
  }

  int rsResult = randomSelect(rsA, 0, n - 1, k, rsStats, print);

  if (print) {
    printf("\nArray end state (RANDOMIZED SELECT):\n");
    util::printArray(rsA, 0, n - 1);

    printf("\n\nOriginal array (SELECT):\n");
    util::printArray(A, 0, n - 1);
  }

  int selResult = select(selA, 0, n - 1, k, selStats, 5, print);

  if (print) {
    printf("\nArray end state (SELECT):\n");
    util::printArray(selA, 0, n - 1);

    printf("\n\n");
  }

  printf("--- RESULTS ---\n");
  printf("Looking for k = %d\n", k);

  printf("\nRANDOMIZED SELECT\n");
  printf("Found value  : %d\n", rsResult);
  printf("Comparisons  : %lld\n", rsStats.comparisons);
  printf("Swaps        : %lld\n", rsStats.swaps);

  printf("\nSELECT\n");
  printf("Found value  : %d\n", selResult);
  printf("Comparisons  : %lld\n", selStats.comparisons);
  printf("Swaps        : %lld\n", selStats.swaps);

  if (print) {
    std::vector<int> sortedA = A;
    sort(sortedA.begin(), sortedA.end());
    printf("\n\nSorted array:\n");
    util::printArray(sortedA, 0, n - 1);
  }

  return 0;
}
