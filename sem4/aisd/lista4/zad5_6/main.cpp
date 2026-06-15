#include <cstdio>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <omp.h>
#include <algorithm>

#include "include/MSTAlgorithms.hpp"

#define  START  200
#define  STOP   7000
#define  STEP   200
#define  REPS   15

template <typename T>
using Vec2D = std::vector<std::vector<T>>;

int calculateRounds(int u, int parent, const Vec2D<int> &adj);

int main() {
  std::ofstream file5("results/task5.csv");
  std::ofstream file6("results/task6.csv");

  if(!file5.is_open() || !file6.is_open()) {
    fprintf(stderr, "[ERROR] Could not open the file/s\n");
    return 1;
  }

  file5 << "n,primTime_ms,kruskalTime_ms\n";
  file6 << "n,avgRounds,minRounds,maxRounds\n";

  for(int n = START; n <= STOP; n += STEP) {
    double primTotalTime = 0;
    double kruskalTotalTime = 0;

    std::vector<int> roundResults(REPS);

    #pragma omp parallel for reduction(+:primTotalTime, kruskalTotalTime)
    for(int r = 0; r < REPS; r++) {
      std::mt19937 localRNG(std::random_device{}() ^ omp_get_thread_num());
      std::uniform_real_distribution<double> dist(0.0, 1.0);

      Vec2D<double> adj(n, std::vector<double>(n, 0.0));
      std::vector<Edge> edges;
      edges.reserve(n * (n - 1) / 2);

      for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
          double w = dist(localRNG);
          adj[i][j] = adj[j][i] = w;
          edges.push_back({i, j, w});
        }
      }

      auto primStart = std::chrono::high_resolution_clock::now();
      prim(n, adj);
      auto primEnd = std::chrono::high_resolution_clock::now();
      primTotalTime += std::chrono::duration<double, std::milli>(primEnd - primStart).count();

      auto kruskalStart = std::chrono::high_resolution_clock::now();
      Vec2D<int> mst = kruskalMST(n, edges);
      auto kruskalEnd = std::chrono::high_resolution_clock::now();
      kruskalTotalTime += std::chrono::duration<double, std::milli>(kruskalEnd - kruskalStart).count();

      std::uniform_int_distribution<int> rootDist(0, n - 1);
      int root = rootDist(localRNG);
      roundResults[r] = calculateRounds(root, -1, mst);
    }

    double primAvg = primTotalTime / REPS;
    double kruskalAvg = kruskalTotalTime / REPS;
    file5 << n << "," << primAvg << "," << kruskalAvg << "\n";

    long long roundsSum = 0;
    int roundsMin = roundResults[0];
    int roundsMax = roundResults[0];

    for(int r = 0; r < REPS; r++) {
      roundsSum += roundResults[r];
      roundsMin = std::min(roundsMin, roundResults[r]);
      roundsMax = std::max(roundsMax, roundResults[r]);
    }

    

    double roundsAvg = static_cast<double>(roundsSum) / REPS;
    file6 << n << "," << roundsAvg << "," << roundsMin << "," << roundsMax << "\n";

    printf("Finished for n=%d | T(prim)=%lfms | T(kruskal)=%lfms | R(avg)=%lf\n", n, primAvg, kruskalAvg, roundsAvg);
  }

  file5.close();
  file6.close();
  printf("Finished. Saved to 'results/task{5, 6}.csv'\n");

  return 0;
}

int calculateRounds(int u, int parent, const Vec2D<int> &adj) {
  std::vector<int> childTimes;

  for(int v : adj[u])
    if(v != parent)
      childTimes.push_back(calculateRounds(v, u, adj));

  if(childTimes.empty())
    return 0;

  sort(childTimes.rbegin(), childTimes.rend());

  int maxTime = 0;
  for(size_t i = 0; i < childTimes.size(); ++i)
    maxTime = std::max(maxTime, childTimes[i] + static_cast<int>(i) + 1);

  return maxTime;
}
