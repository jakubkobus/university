#include <stdio.h>
#include <random>
#include <fstream>
#include <cstring>
#include <ctime>

int runSingleTry(int n, double p, bool *stations, std::mt19937 &generator);

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

  file << "n,try,p,Tn\n";

  clock_t startTime = clock();
  bool *stations = (bool *)calloc(N_END + 1, sizeof(bool));
  int n, k;

  for(n = N_START; n <= N_END; n += N_STEP) {
    for(k = 1; k <= K_TRIES; k++)
      file << n << ","
           << k << ","
           << 0.5 << ","
           << runSingleTry(n, 0.5, stations, generator) << "\n"
           << n << ","
           << k << ","
           << 0.1 << ","
           << runSingleTry(n, 0.1, stations, generator) << "\n";
          
    if(n % 1000 == 0)
      printf("n = %d\n", n);
  }

  clock_t endTime = clock();
  double simulationTime = double(endTime - startTime) / CLOCKS_PER_SEC;

  printf("\nSimulation time: %.2fs\n", simulationTime);
  printf("Saved to '%s'\n", FILENAME.c_str());

  file.close();
  free(stations);
  return 0;
}

int runSingleTry(int n, double p, bool *stations, std::mt19937 &generator) {
  std::uniform_real_distribution<> dist(0.0, 1.0);

  memset(stations, 0, (n + 1) * sizeof(bool));
  stations[0] = true;

  int Tn = 0, 
      informed = 0,
      j;

  while(informed != n) {
    for(j = 1; j <= n; j++)
      if(!stations[j] && dist(generator) < p) {
        stations[j] = true;
        informed++;
      }

    Tn++;
  }

  return Tn;
}
