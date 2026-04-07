#pragma once

#include <vector>

#include "result.hpp"
#include "util.hpp"

#include "insertion.hpp"

inline Result hybridSort(std::vector<int> &arr, int low, int high, int threshold = 10) {
  Result s;

  if (low >= high)
    return s;

  if (high - low < threshold) {
    if (arr.size() < 40)
      printf("Switching to insertion sort for subarray [%d, %d]\n", low, high);
    s = insertionSort(arr, low, high);
  } else {
    if (arr.size() < 40)
      printf("Using quicksort for subarray [%d, %d]\n", low, high);

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

    Result leftStats = hybridSort(arr, low, i);
    Result rightStats = hybridSort(arr, i + 2, high);

    s.comparisons += leftStats.comparisons + rightStats.comparisons;
    s.swaps += leftStats.swaps + rightStats.swaps;
  }

  s.sorted = util::isSorted(arr);
  return s;
}
