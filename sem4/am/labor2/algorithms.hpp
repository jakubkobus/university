#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <limits>

#include "tsp.hpp"

struct SA_Params {
  double initialTemp;
  double alpha;
  int epochs;
  int stepsPerEpoch;
};

struct TS_Params {
  int tabuSize;
  int maxIterations;
  int sampleSize;
};

inline void invert(tsp::Route &route, const int i, const int j) {
  if (
    i < 0 ||
    static_cast<tsp::Route::size_type>(j) >= route.size() ||
    i >= j
  ) return;

  std::reverse(route.begin() + i, route.begin() + j + 1);
}

inline double getInvertDelta(const tsp::Route &route, const int i, const int j) {
  if (i >= j) return 0.0;

  int n = route.size();

  if (i == 0 && j == n - 1)
    return 0.0;

  int iPrev = (i == 0) ? n - 1 : i - 1;
  int jNext = (j == n - 1) ? 0 : j + 1;

  double removedDelta = tsp::calculateDistance(route[iPrev], route[i]) +
                        tsp::calculateDistance(route[j], route[jNext]);
  double addedDelta   = tsp::calculateDistance(route[iPrev], route[j]) +
                        tsp::calculateDistance(route[i], route[jNext]);

  return addedDelta - removedDelta;
}

inline tsp::Route simulatedAnnealing(tsp::Route route, const SA_Params params, std::mt19937 &rng) {
  int n = route.size();
  std::uniform_int_distribution<int> dist(0, n - 1);
  std::uniform_real_distribution<double> probDist(0.0, 1.0);

  tsp::Route bestRoute = route;
  double bestLength = tsp::calculateRouteLength(route);
  double currentLength = bestLength;
  double temp = params.initialTemp;

  for (int e = 0; e < params.epochs; e++) {
    for (int s = 0; s < params.stepsPerEpoch; s++) {
      int i = dist(rng);
      int j = dist(rng);

      if (i == j) continue;
      if (i > j) std::swap(i, j);

      double delta = getInvertDelta(route, i, j);

      if (delta < -1e-6 || probDist(rng) < std::exp(-delta / temp)) {
        invert(route, i, j);
        currentLength += delta;

        if (currentLength < bestLength) {
          bestLength = currentLength;
          bestRoute = route;
        }
      }
    }

    temp *= params.alpha;
  }

  return bestRoute;
}

inline tsp::Route tabuSearch(tsp::Route route, const TS_Params params, std::mt19937 &rng) {
  int n = route.size();
  std::uniform_int_distribution<int> dist(0, n - 1);
  std::vector<std::vector<int>> tabuMatrix(n, std::vector<int>(n, 0));

  tsp::Route bestRoute = route;
  double bestLength = tsp::calculateRouteLength(route);
  double currentLength = bestLength;

  for (int it = 1; it <= params.maxIterations; it++) {
    double bestDelta = std::numeric_limits<double>::max();
    int iBest = -1, jBest = -1;

    for (int k = 0; k < params.sampleSize; k++) {
      int i = dist(rng);
      int j = dist(rng);

      if (i == j) continue;
      if (i > j) std::swap(i, j);

      double delta = getInvertDelta(route, i, j);
      bool isTabu = tabuMatrix[route[i].id - 1][route[j].id - 1] > it;

      if (isTabu && (currentLength + delta < bestLength))
        isTabu = false;

      if (!isTabu && delta < bestDelta) {
        bestDelta = delta;
        iBest = i;
        jBest = j;
      }
    }

    if (iBest != -1) {
      tabuMatrix[route[iBest].id - 1][route[jBest].id - 1] = it + params.tabuSize;
      tabuMatrix[route[jBest].id - 1][route[iBest].id - 1] = it + params.tabuSize;

      invert(route, iBest, jBest);
      currentLength += bestDelta;

      if (currentLength < bestLength) {
        bestLength = currentLength;
        bestRoute = route;
      }
    }
  }

  return bestRoute;
}

#endif // ALGORITHMS_HPP
