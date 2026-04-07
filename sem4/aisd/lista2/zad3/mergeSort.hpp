#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>

inline void merge(
    std::vector<int> &arr,
    int left,
    int mid,
    int right,
    std::vector<int> &temp,
    unsigned long long& comparisons,
    unsigned long long& moves
  ) {

  int i = left;
  int j = mid;
  int k = left;

  while (i < mid && j < right) {
    comparisons++;
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
      moves++;
    } else {
      temp[k++] = arr[j++];
      moves++;
    }
  }

  while (i < mid) {
    temp[k++] = arr[i++];
    moves++;
  }

  while (j < right) {
    temp[k++] = arr[j++];
    moves++;
  }

  for (int x = left; x < right; x++) {
    arr[x] = temp[x];
    moves++;
  }
}

inline void mergeSortRec(
    std::vector<int> &arr,
    int left,
    int right,
    std::vector<int> &temp,
    unsigned long long& comparisons,
    unsigned long long& moves
  ) {

  if (right - left <= 1)
    return;

  int mid = left + (right - left) / 2;

  mergeSortRec(arr, left, mid, temp, comparisons, moves);
  mergeSortRec(arr, mid, right, temp, comparisons, moves);

  merge(arr, left, mid, right, temp, comparisons, moves);
}

inline void mergeSort(
    std::vector<int> &arr,
    unsigned long long& comparisons,
    unsigned long long& moves
  ) {

  std::vector<int> temp(arr.size());
  mergeSortRec(arr, 0, arr.size(), temp, comparisons, moves);
}

#endif // MERGESORT_HPP
