#include <cstdio>
#include <vector>
#include <string>
#include <omp.h>
#include <filesystem>

#include "tsp.hpp"
#include "algorithms.hpp"

void run(const std::string &filename, const std::string &algo, const int k);

int main() {
  std::vector<std::string> files = {
    "mu1979.tsp", "ca4663.tsp", "tz6117.tsp", "eg7146.tsp", "ei8246.tsp"
  };

  int tries = 100;

  for (const auto &file : files) {
    std::string filename = "data/" + file;
    run(filename, "SA", tries);
    run(filename, "TS", tries);
  }

  return 0;
}

void run(const std::string &filename, const std::string &algo, const int k) {
  tsp::Route baseNodes;

  try {
    baseNodes = tsp::load(filename);
  } catch (const std::exception &e) {
    fprintf(stderr, "%s\n", e.what());
    return;
  }

  int n = baseNodes.size();
  double totalLength = 0;
  double bestOverallLength = std::numeric_limits<double>::max();
  tsp::Route bestOverallRoute;

  const SA_Params bestParamsSA {
    .initialTemp = 1000.0,
    .alpha = 0.95,
    .epochs = 10000,
    .stepsPerEpoch = n * 2
  };

  const TS_Params bestParamsTS {
    .tabuSize = n / 20,
    .maxIterations = 10000,
    .sampleSize = n * 2
  };

  printf("\n--- %s | Algorithm: %s | Tries: %d ---\n", filename.c_str(), algo.c_str(), k);

  #pragma omp parallel
  {
    std::mt19937 rng(std::random_device{}() + omp_get_thread_num());

    #pragma omp for reduction(+:totalLength)
    for (int iter = 0; iter < k; iter++) {
      tsp::Route currentRoute = baseNodes;
      std::shuffle(currentRoute.begin(), currentRoute.end(), rng);

      tsp::Route resultRoute;

      resultRoute = (algo == "SA")
        ? simulatedAnnealing(
          currentRoute,
          bestParamsSA,
          rng
        )
        : tabuSearch(
          currentRoute,
          bestParamsTS,
          rng
        );

      double resultLength = tsp::calculateRouteLength(resultRoute);
      totalLength += resultLength;

      #pragma omp critical
      {
        if (resultLength < bestOverallLength) {
          bestOverallLength = resultLength;
          bestOverallRoute = resultRoute;
        }
      }
    }
  }

  printf("> Average solution length: %lf\n", (totalLength / k));
  printf("> Best solution length: %lf\n", bestOverallLength);

  std::string fileNoExt = std::filesystem::path(filename).stem().string();
  tsp::saveRoute(
      bestOverallRoute,
      "results/txt/" + algo + "_" + fileNoExt + "_bestRoute.txt"
  );
}
