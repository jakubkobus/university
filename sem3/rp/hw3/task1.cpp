#include <stdio.h>
#include <random>
#include <fstream>
#include <ctime>
#include <string>
#include <cstring>

struct SimulationResult {
  int aMaxLoad;
  int bMaxLoad;
};

SimulationResult runSingleTry(int n, int *d1, int *d2, std::mt19937 &generator);

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

  file << "n,try,aMaxLoad,bMaxLoad\n";

  clock_t startTime = clock();
  SimulationResult res;
  int *d1 = (int *)malloc((N_END) * sizeof(int)),
      *d2 = (int *)malloc((N_END) * sizeof(int)),
      n, k;

  for(n = N_START; n <= N_END; n += N_STEP) {
    for(k = 1; k <= K_TRIES; k++) {
      res = runSingleTry(n, d1, d2, generator);
      file << n << ","
           << k << ","
           << res.aMaxLoad << ","
           << res.bMaxLoad << "\n";
    }

    if(n % 100000 == 0)
      printf("n = %d\n", n);
  }

  clock_t endTime = clock();
  double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;

  printf("\nSimulation time: %.2fs\n", simulationTime);
  printf("Saved to '%s'\n", FILENAME.c_str());

  file.close();
  free(d1); free(d2);
  return 0;
}

SimulationResult runSingleTry(int n, int *d1, int *d2, std::mt19937 &generator) {
  std::uniform_int_distribution<> dist(0, n - 1);
  SimulationResult res = { 0, 0 };

  memset(d1, 0, n * sizeof(int));
  memset(d2, 0, n * sizeof(int));

  int i, choice1, choice2, chosen;
  for(i = 0; i < n; i++) {
    choice1 = dist(generator);
    d1[choice1]++;

    if(d1[choice1] > res.aMaxLoad)
      res.aMaxLoad = d1[choice1];

    choice1 = dist(generator);
    choice2 = dist(generator);

    chosen = (d2[choice1] <= d2[choice2]) ? choice1 : choice2;
    d2[chosen]++;

    if(d2[chosen] > res.bMaxLoad)
      res.bMaxLoad = d2[chosen];
  }

  return res;
}