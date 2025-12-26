#include <stdio.h>
#include <random>
#include <fstream>
#include <ctime>
#include <string>

#define K_TRIES   50
#define N_START   1000
#define N_END     100000
#define N_STEP    1000
#define FILENAME  "./results/results.csv"

struct SimulationResult {
  int Bn;
  int Un;
  int Cn;
  int Dn;
};

SimulationResult runSingleTry(int n, std::mt19937 &generator);

int main() {
  std::random_device rd;
  std::mt19937 generator(rd());

  std::ofstream file(FILENAME);
  if(!file.is_open()) {
    fprintf(stderr, "Error while opening the file '%s'\n", FILENAME);
    return 1;
  }

  file << "n,try,B,U,C,D\n";

  clock_t startTime = clock();

  SimulationResult res;

  for(int n = N_START; n <= N_END; n += N_STEP) {
    for(int k = 0; k < K_TRIES; k++) {
      res = runSingleTry(n, generator);
      file << n      << "," 
           << k      << ","
           << res.Bn << ","
           << res.Un << ","
           << res.Cn << ","
           << res.Dn << "\n";
    }

    if(n % 10000 == 0)
      printf("n = %d\n", n);
  }

  clock_t endTime = clock();
  double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;

  printf("\nSimulation time: %.2fs\n", simulationTime);
  printf("Saved to '%s'\n", FILENAME);

  file.close();
  return 0;
}

SimulationResult runSingleTry(int n, std::mt19937 &generator) {
  std::uniform_int_distribution<> dist(0, n - 1);
  SimulationResult res = {0, 0, 0, 0};
  bool firstCollision = false;
  int *bins = (int*)calloc(n, sizeof(int)),
      ballsThrown = 0,
      filledBins = 0,
      doubleFilledBins = 0,
      idx, countBefore;

  while(doubleFilledBins < n) {
    idx = dist(generator);
    ballsThrown++;

    countBefore = bins[idx]++;

    if(!firstCollision && countBefore > 0) {
      res.Bn = ballsThrown;
      firstCollision = true;
    }

    if(countBefore == 0) {
      filledBins++;
      if(filledBins == n)
        res.Cn = ballsThrown;
    }

    if(countBefore == 1) {
      doubleFilledBins++;
      if(doubleFilledBins == n)
        res.Dn = ballsThrown;
    }

    if(ballsThrown == n)
      res.Un = n - filledBins;
  }

  if(res.Bn == 0)
    res.Bn = ballsThrown;

  free(bins);
  return res;
}
