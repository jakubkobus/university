#include <stdio.h>
#include <random>
#include <fstream>
#include <ctime>

struct SortStats {
  int comparisons;
  int swaps;
};

SortStats runSingleTry(int n, std::mt19937 &generator);
SortStats insertionSort(int arr[], int n);

int main(int argc, char *argv[]) {
  if(argc != 6) {
    fprintf(stderr, "Usage: %s <start> <end> <step> <tries> <output_path>\n", argv[0]);
    return 1;
  }

  const int N_START = std::stoi(argv[1]);
  const int N_END   = std::stoi(argv[2]);
  const int N_STEP  = std::stoi(argv[3]);
  const int K_TRIES = std::stoi(argv[4]);
  const std::string FILENAME = argv[5];

  std::random_device rd;
  std::mt19937 generator(rd());

  std::ofstream file(FILENAME);
  if(!file.is_open()) {
    fprintf(stderr, "Error while opening the file '%s'\n", FILENAME.c_str());
    return 1;
  }

  file << "n,try,comparisons,swaps\n";

  clock_t startTime = clock();
  SortStats res;
  int n, k;

  for(n = N_START; n <= N_END; n += N_STEP) {
    for(k = 1; k <= K_TRIES; k++) {
      res = runSingleTry(n, generator);

      file << n << ","
           << k << ","
           << res.comparisons << "," 
           << res.swaps << "\n";
    }

    if(n % 1000 == 0)
      printf("n = %d\n", n);
  }

  clock_t endTime = clock();
  double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;

  printf("\nSimulation time: %.2fs\n", simulationTime);
  printf("Saved to '%s'\n", FILENAME.c_str());

  file.close();
  return 0;
}

SortStats runSingleTry(int n, std::mt19937 &generator) {
  std::uniform_int_distribution<> dist(1, n);

  int i, A[n];
  for(i = 0; i < n; i++)
    A[i] = dist(generator);

  return insertionSort(A, n);
} 

SortStats insertionSort(int arr[], int n) {
  SortStats stats = { 0, 0 };
  int i, j, key;

  for(i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;

    while(j >= 0) {
      stats.comparisons++;

      if(arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
        stats.swaps++;
      } else break;
    }

    arr[j + 1] = key;
  }

  return stats;
}