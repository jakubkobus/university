#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <omp.h>
#include <limits>
#include <algorithm>
#include <random>

#include "tsp.hpp"
#include "algorithms.hpp"

void SA_BruteForce_Test(const std::vector<std::string> &files);
void TS_BruteForce_Test(const std::vector<std::string> &files);

int main() {
  std::vector<std::string> files = {
    "wi29.tsp", "dj38.tsp", "qa194.tsp", "uy734.tsp", "zi929.tsp"
  };

  SA_BruteForce_Test(files);
  TS_BruteForce_Test(files);

  return 0;
}

void SA_BruteForce_Test(const std::vector<std::string> &files) {
  std::ofstream csv("analysis/sa_bruteforce_test.csv");
  csv << "file,initialTemperature,alpha,epochs,stepsPerEpoch,avgLength,bestLength\n";

  std::vector<double> temps = { 100.0, 1000.0, 5000.0 };
  std::vector<double> alphas = { 0.8, 0.85, 0.9, 0.95, 0.99 };
  std::vector<int> epochs = { 1000, 5000, 10000 };

  for (const auto &file : files) {
    tsp::Route baseNodes = tsp::load("data/" + file);
    int n = baseNodes.size();
    int k = 50;

    std::vector<int> steps = { n / 4, n / 2, n, n * 2 };

    for (double t : temps) {
      for (double a : alphas) {
        for (int e : epochs) {
          for (int s : steps) {
            double totalLength = 0;
            double globalBest = std::numeric_limits<double>::max();

            #pragma omp parallel
            {
              std::mt19937 rng(std::random_device{}() + omp_get_thread_num());

              #pragma omp for reduction(+:totalLength)
              for (int i = 0; i < k; i++) {
                tsp::Route currentRoute = baseNodes;
                std::shuffle(currentRoute.begin(), currentRoute.end(), rng);

                tsp::Route res = simulatedAnnealing(currentRoute, SA_Params{t, a, e, s}, rng);
                double len = tsp::calculateRouteLength(res);

                totalLength += len;

                #pragma omp critical
                {
                  if (len < globalBest)
                    globalBest = len;
                }
              }
            }

            double avgLen = totalLength / k;

            csv << file << "," << t << "," << a << "," << e << "," << s << "," << avgLen << "," << globalBest << "\n";
            printf(
              "[SA][%s] T:%.0f | A:%.3f | Ep:%d | Stp:%d -> Err: %.2f\n",
              file.c_str(), t, a, e, s, avgLen
            );
          }
        }
      }
    }
  }

  csv.close();
}

void TS_BruteForce_Test(const std::vector<std::string> &files) {
  std::ofstream csv("analysis/ts_bruteforce_test.csv");
  csv << "file,tabuSize,maxIterations,sampleSize,avgLength,bestLength\n";

  std::vector<int> iterations = { 1000, 5000, 10000 };

  for (const auto &file : files) {
    tsp::Route baseNodes = tsp::load("data/" + file);
    int n = baseNodes.size();
    int k = 50;

    std::vector<int> tabu = { n / 40, n / 20, n / 10, n / 5, n / 2 };
    std::vector<int> samples = { n / 4, n / 2, n, n * 2 };

    for (int t : tabu) {
      t = std::max(2, t);

      for (int i : iterations) {
        for (int s : samples) {
          double totalLength = 0;
          double globalBest = std::numeric_limits<double>::max();

          #pragma omp parallel
          {
            std::mt19937 rng(std::random_device{}() + omp_get_thread_num());

            #pragma omp for reduction(+:totalLength)
            for (int j = 0; j < k; j++) {
              tsp::Route currentRoute = baseNodes;
              std::shuffle(currentRoute.begin(), currentRoute.end(), rng);

              tsp::Route res = tabuSearch(currentRoute, TS_Params{t, i, s}, rng);
              double len = tsp::calculateRouteLength(res);

              totalLength += len;

              #pragma omp critical
              {
                if (len < globalBest)
                  globalBest = len;
              }
            }
          }

          double avgLen = totalLength / k;

          csv << file << "," << t << "," << i << "," << s << "," << avgLen << "," << globalBest << "\n";
          printf(
            "[TS][%s] Tabu:%d | Iter:%d | Samp:%d -> avgLen: %.2f\n",
            file.c_str(), t, i, s, avgLen
          );
        }
      }
    }
  }

  csv.close();
}
