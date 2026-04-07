#pragma once

#include <vector>
#include <stdio.h>

namespace util {
  inline void printArray(std::vector<int> arr) {
    printf("[ ");
    for (int i = 0; i < (int)arr.size(); i++) {
      if (arr.size() < 40)
        printf("%02d ", arr[i]);
      else
        printf("%d ", arr[i]);
    }
    printf("]\n");
  }

  inline bool isSorted(std::vector<int> arr) {
    for (int i = 0; i < (int)arr.size() - 1; i++)
      if (arr[i] > arr[i + 1])
        return false;
    return true;
  }

  inline bool compare(int a, int b, int &comparisons) {
    comparisons++;
    return a < b;
  }

  inline void swap(int &a, int &b, int &swaps) {
    swaps++;
    int temp = a;
    a = b;
    b = temp;
  }
}
