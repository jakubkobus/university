#pragma once

#include <stdio.h>
#include <vector>
#include <utility>

#include "stats.hpp"

namespace util {
  inline void printArray(const std::vector<int> &A, const int p, const int q) {
    printf("[ ");

    for (int i = p; i <= q; i++)
      printf("%d ", A[i]);

    printf("]\n");
  }

  inline void swapElements(std::vector<int> &A, const int i, const int j, Stats &stats) {
    if (i != j) {
      std::swap(A[i], A[j]);
      stats.swaps++;
    }
  }

  inline int partition(std::vector<int> &A, const int p, const int q, const int pivot, Stats &stats, bool print = false) {
    for (int i = p; i <= q; i++) {
      stats.comparisons++;

      if (A[i] == pivot) {
        swapElements(A, i, q, stats);
        break;
      }
    }

    int x = A[q];
    int i = p - 1;
    for (int j = p; j < q; j++) {
      stats.comparisons++;

      if (A[j] <= x) {
        i++;
        swapElements(A, i, j, stats);
      }
    }

    swapElements(A, i + 1, q, stats);

    if (print) {
      printf("    After partition (pivot = %d): ", x);
      printArray(A, p, q);
    }

    return i + 1;
  }

  inline void insertionSort(std::vector<int>& A, int p, int q, Stats& stats) {
    for (int i = p + 1; i <= q; ++i) {
      int key = A[i];
      int j = i - 1;

      while (j >= p) {
        stats.comparisons++;
        if (A[j] > key) {
          A[j + 1] = A[j];
          stats.swaps++;
          j--;
        } else break;
      }

      A[j + 1] = key;
      stats.swaps++;
    }
  }
}
