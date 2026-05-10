#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <omp.h>
#include <filesystem>

#include "tsp.hpp"

struct Stats {
  double finalLength;
  int steps;
};

void invert(tsp::Route &route, const int i, const int j);
void transpose(tsp::Route &route, const int i, const int j);
double getInvertDelta(const tsp::Route &route, const int i, const int j);
double getTransposeDelta(const tsp::Route &route, int i, int j);
Stats localSearchInvertFull(tsp::Route &route);
Stats localSearchInvertRandomPartial(tsp::Route &route, std::mt19937 &rng);
Stats localSearchTransposeFull(tsp::Route &route);
void run(const std::string &filename, int taskNumber);

int main() {
  std::vector<std::string> prevList = {
    "wi29.tsp", "dj38.tsp", "qa194.tsp", "uy734.tsp", "zi929.tsp"
  };
  std::vector<std::string> currList = {
    "mu1979.tsp", "ca4663.tsp", "tz6117.tsp", "eg7146.tsp", "ei8246.tsp"
  };

  std::vector<std::string> allFiles;
  allFiles.insert(allFiles.end(), prevList.begin(), prevList.end());
  allFiles.insert(allFiles.end(), currList.begin(), currList.end());

  for (const auto &file : allFiles) {
    std::string filename = "data/" + file;
    run(filename, 1);
    run(filename, 2);
    run(filename, 3);
  }
  return 0;
}

void invert(tsp::Route &route, const int i, const int j) {
  if (
    i < 0 ||
    static_cast<tsp::Route::size_type>(j) >= route.size() ||
    i >= j
  ) return;

  std::reverse(route.begin() + i, route.begin() + j + 1);
}

void transpose(tsp::Route &route, const int i, const int j) {
  if (
    i < 0 ||
    static_cast<tsp::Route::size_type>(j) >= route.size() ||
    i >= j
  ) return;

  std::swap(route[i], route[j]);
}

double getInvertDelta(const tsp::Route &route, const int i, const int j) {
  if (i >= j) return 0.0;
  int n = route.size();
  if (i == 0 && j == n - 1) return 0.0;

  int prev_i = (i == 0) ? n - 1 : i - 1;
  int next_j = (j == n - 1) ? 0 : j + 1;

  double d_removed = tsp::calculateDistance(route[prev_i], route[i]) +
                      tsp::calculateDistance(route[j], route[next_j]);
  double d_added = tsp::calculateDistance(route[prev_i], route[j]) +
                    tsp::calculateDistance(route[i], route[next_j]);

  return d_added - d_removed;
}

double getTransposeDelta(const tsp::Route &route, int i, int j) {
  if (i >= j) return 0.0;
  int n = route.size();

  int prev_i = (i == 0) ? n - 1 : i - 1;
  int next_i = (i == n - 1) ? 0 : i + 1;
  int prev_j = (j == 0) ? n - 1 : j - 1;
  int next_j = (j == n - 1) ? 0 : j + 1;

  if (j == i + 1) {
    double d_removed = tsp::calculateDistance(route[prev_i], route[i]) +
                       tsp::calculateDistance(route[j], route[next_j]);
    double d_added = tsp::calculateDistance(route[prev_i], route[j]) +
                     tsp::calculateDistance(route[i], route[next_j]);
    return d_added - d_removed;
  }

  else if (i == 0 && j == n - 1) {
    double d_removed = tsp::calculateDistance(route[n-2], route[n-1]) +
                       tsp::calculateDistance(route[0], route[1]);
    double d_added = tsp::calculateDistance(route[n-2], route[0]) +
                     tsp::calculateDistance(route[n-1], route[1]);
    return d_added - d_removed;
  }

  double d_removed = tsp::calculateDistance(route[prev_i], route[i]) +
                     tsp::calculateDistance(route[i], route[next_i]) +
                     tsp::calculateDistance(route[prev_j], route[j]) +
                     tsp::calculateDistance(route[j], route[next_j]);

  double d_added = tsp::calculateDistance(route[prev_i], route[j]) +
                   tsp::calculateDistance(route[j], route[next_i]) +
                   tsp::calculateDistance(route[prev_j], route[i]) +
                   tsp::calculateDistance(route[i], route[next_j]);

  return d_added - d_removed;
}

Stats localSearchInvertFull(tsp::Route &route) {
  int n = route.size();
  int steps = 0;

  while (true) {
    double bestDelta = 0.0;
    int best_i = -1, best_j = -1;

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        double delta = getInvertDelta(route, i, j);
        if (delta < bestDelta) {
          bestDelta = delta;
          best_i = i;
          best_j = j;
        }
      }
    }

    if (bestDelta < -1e-6) {
      invert(route, best_i, best_j);
      steps++;
    } else {
      break;
    }
  }
  return { tsp::calculateRouteLength(route), steps };
}

Stats localSearchInvertRandomPartial(tsp::Route &route, std::mt19937 &rng) {
  int n = route.size();
  int steps = 0;
  std::uniform_int_distribution<int> dist(0, n - 1);

  while (true) {
    double bestDelta = 0.0;
    int best_i = -1, best_j = -1;

    for (int k = 0; k < n; k++) {
      int i = dist(rng);
      int j = dist(rng);
      if (i == j) continue;
      if (i > j) std::swap(i, j);

      double delta = getInvertDelta(route, i, j);
      if (delta < bestDelta) {
        bestDelta = delta;
        best_i = i;
        best_j = j;
      }
    }

    if (bestDelta < -1e-6) {
      invert(route, best_i, best_j);
      steps++;
    } else {
      break;
    }
  }
  return { tsp::calculateRouteLength(route), steps };
}

Stats localSearchTransposeFull(tsp::Route &route) {
  int n = route.size();
  int steps = 0;

  while (true) {
    double bestDelta = 0.0;
    int best_i = -1, best_j = -1;

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        double delta = getTransposeDelta(route, i, j);
        if (delta < bestDelta) {
          bestDelta = delta;
          best_i = i;
          best_j = j;
        }
      }
    }

    if (bestDelta < -1e-6) {
      transpose(route, best_i, best_j);
      steps++;
    } else {
      break;
    }
  }
  return { tsp::calculateRouteLength(route), steps };
}

void run(const std::string &filename, int taskNumber) {
  tsp::Route baseNodes;
  try {
    baseNodes = tsp::load(filename);
  } catch (const std::exception& e) {
    fprintf(stderr, "%s\n", e.what());
    return;
  }

  int n = baseNodes.size();

  // int numPermutations = n;
  int numPermutations = 10;

  double totalLength = 0;
  long long totalSteps = 0;
  double bestOverallLength = std::numeric_limits<double>::max();
  tsp::Route bestOverallRoute;

  printf("\n--- File: %s | Task: %d | Vertices: %d ---\n", filename.c_str(), taskNumber, n);
  printf("Processing %d iteration...\n", numPermutations);

  #pragma omp parallel
  {
    std::mt19937 rng(std::random_device{}());

    #pragma omp for reduction(+:totalLength, totalSteps)
    for (int iter = 0; iter < numPermutations; iter++) {
      tsp::Route currentRoute = baseNodes;
      std::shuffle(currentRoute.begin(), currentRoute.end(), rng);

      Stats stats;
      if (taskNumber == 1) {
        stats = localSearchInvertFull(currentRoute);
      } else if (taskNumber == 2) {
        stats = localSearchInvertRandomPartial(currentRoute, rng);
      } else {
        stats = localSearchTransposeFull(currentRoute);
      }

      totalLength += stats.finalLength;
      totalSteps += stats.steps;

      #pragma omp critical
      if (stats.finalLength < bestOverallLength) {
        bestOverallLength = stats.finalLength;
        bestOverallRoute = currentRoute;
      }
    }
  }

  printf("> Average solution value: %lf\n", (totalLength / numPermutations));
  printf("> Average steps to improve: %lf\n", (static_cast<double>(totalSteps) / numPermutations));
  printf("> Best achieved solution: %lf\n", bestOverallLength);

  std::string fileNoExt = std::filesystem::path(filename).stem().string();
  tsp::saveRoute(
    bestOverallRoute,
    "results/task" + std::to_string(taskNumber) + "_" + fileNoExt + "_bestRoute.txt"
  );
}
