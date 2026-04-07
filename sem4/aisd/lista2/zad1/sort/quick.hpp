#pragma once

#include <vector>

#include "result.hpp"
#include "util.hpp"

inline Result quickSort(std::vector<int> &arr, int low, int high) {
  Result s;

  if (low < high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
      if (util::compare(arr[j], pivot, s.comparisons)) {
        i++;
        util::swap(arr[i], arr[j], s.swaps);
      }
    }

    util::swap(arr[i + 1], arr[high], s.swaps);

    if (arr.size() < 40)
      util::printArray(arr);

    Result leftStats = quickSort(arr, low, i);
    Result rightStats = quickSort(arr, i + 2, high);

    s.comparisons += leftStats.comparisons + rightStats.comparisons;
    s.swaps += leftStats.swaps + rightStats.swaps;
  }

  s.sorted = util::isSorted(arr);
  return s;
}
