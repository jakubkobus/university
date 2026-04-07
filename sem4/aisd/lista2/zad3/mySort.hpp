#ifndef MYSORT_HPP
#define MYSORT_HPP

#include <vector>
#include "mergeSort.hpp"

inline void mySort(
    std::vector<int> &arr,
    unsigned long long &comparisons,
    unsigned long long &moves
  ) {

  int n = arr.size();
  if (n <= 1)
    return;

  std::vector<int> runs;
  runs.push_back(0);

  for (int i = 1; i < n; ++i) {
    comparisons++;
    if (arr[i] < arr[i - 1]) {
      runs.push_back(i);
    }
  }

  runs.push_back(n);

  std::vector<int> temp(n);

  while (runs.size() > 2) {
    std::vector<int> next_runs;
    next_runs.push_back(0);

    for (size_t i = 0; i < runs.size() - 1; i += 2) {
      if (i + 2 < runs.size()) {
        int left = runs[i];
        int mid = runs[i + 1];
        int right = runs[i + 2];

        merge(arr, left, mid, right, temp, comparisons, moves);

        next_runs.push_back(right);
      } else {
        next_runs.push_back(runs[i + 1]);
      }
    }

    runs = next_runs;
  }
}

#endif // MYSORT_HPP
