#pragma once
#include <vector>
#include <algorithm>

#include "stats.hpp"
#include "util.hpp"

inline int select(std::vector<int> &A, const int p, const int q, const int k, Stats &stats, const int divSize = 5, bool print = false) {
  if (print) {
    printf("  SELECT in: ");
    util::printArray(A, p, q);
  }

  if (p == q) return A[p];

  int n = q - p + 1;
  std::vector<int> medians;

  int subLeft, subRight, medianIdx;
  for (int i = 0; i < n; i += divSize) {
    subLeft = p + i;
    subRight = std::min(p + i + divSize - 1, q);

    util::insertionSort(A, subLeft, subRight, stats);

    medianIdx = subLeft + (subRight - subLeft) / 2;
    medians.push_back(A[medianIdx]);
  }

  int pivot;
  if (medians.size() == 1) {
    pivot = medians[0];
  } else {
    int kMedian = medians.size() / 2 + (medians.size() % 2 != 0 ? 1 : 0);
    pivot = select(medians, 0, medians.size() - 1, kMedian, stats, divSize);
  }

  int r = util::partition(A, p, q, pivot, stats, print);
  int j = r - p + 1;

  if (k == j) return A[r];
  if (k < j) return select(A, p, r - 1, k, stats, divSize, print);
  else return select(A, r + 1, q, k - j, stats, divSize, print);
}
