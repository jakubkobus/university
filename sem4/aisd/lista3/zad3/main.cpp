#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <omp.h>

#include "../zad1/select.hpp"

int main() {
  const std::string FILENAME = "task3_results.csv";
  std::ofstream file(FILENAME);
  file << "n,divSize,avgComparisons,avgSwaps\n";

  const int K = 50;
  std::vector<int> groups = { 3, 5, 7, 9, 19, 21 };

  long long comparisons, swaps;
  for (int n = 100; n <= 50000; n += 100) {
    if (n % 5000 == 0)
      printf("Processing n = %d ...\n", n);

    for (int divSize : groups) {
      comparisons = 0;
      swaps = 0;

      #pragma omp parallel for reduction(+:comparisons, swaps)
      for (int j = 0; j < K; j++) {

        std::mt19937 rngLocal(std::random_device{}() + omp_get_thread_num());
        std::uniform_int_distribution<int> dist(0, 2 * n - 1);

        std::vector<int> data(n);
        for (int i = 0; i < n; i++)
          data[i] = dist(rngLocal);

        int k_stat = n / 2;
        Stats stats;
        select(data, 0, n - 1, k_stat, stats, divSize);

        comparisons += stats.comparisons;
        swaps += stats.swaps;
      }

      file << n << "," << divSize << "," << comparisons / K << "," << swaps / K << "\n";
    }
  }

  file.close();
  printf("Results saved to '%s'\n", FILENAME.c_str());
  return 0;
}
