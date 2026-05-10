#pragma once
#include <vector>
#include <random>

#include "stats.hpp"
#include "util.hpp"

inline int randomPartition(std::vector<int> &A, const int p, const int q, Stats &stats, bool print = false) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(p, q);

  int i = dist(rng);
  util::swapElements(A, i, q, stats);
  return util::partition(A, p, q, A[q], stats, print);
}

inline int randomSelect(std::vector<int> &A, const int p, const int q, const int k, Stats &stats, bool print = false) {
  if (print) {
    printf("  RANDOMIZED SELECT in: ");
    util::printArray(A, p, q);
  }

  if (p == q) return A[p];

  int r = randomPartition(A, p, q, stats, print);
  int j = r - p + 1;

  if (k == j) return A[r];
  if (k < j) return randomSelect(A, p, r - 1, k, stats, print);
  else return randomSelect(A, r + 1, q, k - j, stats, print);
}
