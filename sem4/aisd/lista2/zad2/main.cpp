#include "../zad1/sort/hybrid.hpp"
#include "../zad1/sort/insertion.hpp"
#include "../zad1/sort/quick.hpp"

#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <omp.h>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Uzycie: %s <algo> <size> <k>\n", argv[0]);
    return 1;
  }

  const std::string GENERATOR_PATH = "../zad1/generator";

  std::string algo = argv[1];
  int size = std::atoi(argv[2]);
  int k = std::atoi(argv[3]);

  int threshold = (size < 1000) ? 4 : 30;

  std::string filename = "results/result_" + algo + "_" + std::to_string(size) + "_" + std::to_string(k) + ".csv";
  FILE *csv = fopen(filename.c_str(), "w");
  if (!csv) {
    fprintf(stderr, "Could not open CSV file\n");
    return 1;
  }

  fprintf(csv, "algo,size,repetition,comparisons,swaps\n");

  #pragma omp parallel for
  for (int i = 1; i <= k; i++) {
    std::string cmd = GENERATOR_PATH + " " + std::to_string(size) + " rand";

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
      fprintf(stderr, "Generator could not be executed.\n");
      fclose(csv);
      exit(1);
    }

    int n;
    if (fscanf(pipe, "%d", &n) != 1) {
      fprintf(stderr, "Could not read size from generator %d\n", i);
      pclose(pipe);
      continue;
    }

    std::vector<int> arr(n);
    for (int j = 0; j < n; j++) {
      fscanf(pipe, "%d", &arr[j]);
    }

    pclose(pipe);

    Result res;
    if (algo == "insertion") {
      res = insertionSort(arr, 0, n - 1);
    } else if (algo == "quick") {
      res = quickSort(arr, 0, n - 1);
    } else if (algo == "hybrid") {
      res = hybridSort(arr, 0, n - 1, threshold);
    }

    #pragma omp critical
    {
      fprintf(csv, "%s,%d,%d,%d,%d\n", algo.c_str(), size, i, res.comparisons, res.swaps);
    }
  }

  fclose(csv);

  return 0;
}
