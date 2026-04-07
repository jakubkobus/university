#include <cstdio>
#include <vector>
#include <random>
#include <limits>

#include "../zad1/sort/hybrid.hpp"

#define SIZE 10000
#define REPS 50
#define START_THRESH 2
#define STOP_THRESH 60

void fill(std::vector<int> &arr, std::mt19937 &rng) {
  std::uniform_int_distribution<int> dist(0, 2 * SIZE - 1);
  for (int i = 0; i < SIZE; i++)
    arr[i] = dist(rng);
}

int main() {
  std::mt19937 rng(std::random_device{}());
  std::vector<int> arr(SIZE);

  long long minOps = std::numeric_limits<long long>::max();
  int bestThreshold = START_THRESH;

  long long currentOps;
  Result res;
  for (int t = START_THRESH, i; t <= STOP_THRESH; t++) {
    currentOps = 0;

    for (i = 0; i < REPS; i++) {
      fill(arr, rng);

      res = hybridSort(arr, 0, SIZE - 1, t);

      currentOps += (res.comparisons + res.swaps);
    }

    if (currentOps < minOps) {
      minOps = currentOps;
      bestThreshold = t;
    }
  }

  printf("bestThreshold=%d\n", bestThreshold);

  return 0;
}
