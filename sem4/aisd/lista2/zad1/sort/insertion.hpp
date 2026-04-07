#pragma once

#include <vector>

#include "result.hpp"
#include "util.hpp"

inline Result insertionSort(std::vector<int> &arr, int low, int high) {
  Result s;

  for (int i = low + 1; i <= high; i++) {
    int j = i;

    while (j > low && util::compare(arr[j], arr[j - 1], s.comparisons)) {
      util::swap(arr[j], arr[j - 1], s.swaps);
      j--;
    }

    if (arr.size() < 40)
      util::printArray(arr);
  }

  s.sorted = util::isSorted(arr);
  return s;
}
