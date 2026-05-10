#include <stdio.h>
#include <vector>
#include <random>
#include <fstream>

#include "../zad1/randomSelect.hpp"
#include "../zad1/select.hpp"

int main() {
  const std::string FILENAME = "task2_results.csv";
  std::ofstream file(FILENAME);
  file << "n,kType,algo,avgComparisons,avgSwaps\n";

  std::mt19937 rng(std::random_device{}());
  const int K = 50;

  for (int n = 100; n <= 50000; n += 100) {
    if (n % 5000 == 0)
      printf("Processing n = %d ...\n", n);

    std::vector<std::pair<std::string, int>> kValues = {
      { "min", 1 },
      { "median", n / 2 },
      { "max", n }
    };

    long long rsComparisons, rsSwaps, selComparisons, selSwaps;
    for (auto const& [name, k] : kValues) {
      rsComparisons = 0;
      rsSwaps = 0;
      selComparisons = 0;
      selSwaps = 0;

      for (int j = 0; j < K; j++) {
        std::vector<int> data(n);
        std::uniform_int_distribution<int> dist(0, 2 * n - 1);
        for (int i = 0; i < n; i++)
          data[i] = dist(rng);

        std::vector<int> rsData = data;
        std::vector<int> selData = data;
        Stats rsStats;
        Stats selStats;

        randomSelect(rsData, 0, n - 1, k, rsStats);
        rsComparisons += rsStats.comparisons;
        rsSwaps += rsStats.swaps;

        select(selData, 0, n - 1, k, selStats);
        selComparisons += selStats.comparisons;
        selSwaps += selStats.swaps;
      }

      file << n << "," << name << ",RandomSelect,"
           << rsComparisons / K << "," << rsSwaps / K << "\n";
      file << n << "," << name << ",Select,"
           << selComparisons / K << "," << selSwaps / K << "\n";
    }
  }

  file.close();
  printf("Results saved to '%s'\n", FILENAME.c_str());
  return 0;
}
