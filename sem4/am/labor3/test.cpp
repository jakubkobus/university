#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <omp.h>

#include "include/tsp.hpp"
#include "include/ga.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " <file1.tsp> <file2.tsp> ...\n";
      return 1;
    }

    std::ofstream out("results/experiments.csv");
    out << "instance,pop_size,cross_rate,mut_rate,cx_type,avg_best_dist,time_seconds\n";

    std::vector<int> pop_sizes = {50, 100, 200};
    std::vector<double> cross_rates = {0.7, 0.8, 0.9};
    std::vector<double> mut_rates = {0.01, 0.05, 0.1};
    std::vector<std::string> cx_types = {"OX", "PMX"};
    int generations = 200;
    int executions = 10;

    for (int file_idx = 1; file_idx < argc; ++file_idx) {
      std::string filename = argv[file_idx];
      std::string instance_name = std::filesystem::path(filename).stem().string();

      std::cout << "\n[INFO] Starting parameter grid search for: " << instance_name << "\n";
      auto nodes = tsp::load(filename);
      ga::DistanceMatrix dm(nodes);

      for (const auto& cx : cx_types) {
        for (int pop : pop_sizes) {
          for (double cr : cross_rates) {
            for (double mr : mut_rates) {
              double total_dist = 0;
              double start_time = omp_get_wtime();

              #pragma omp parallel for reduction(+:total_dist) schedule(dynamic)
              for (int i = 0; i < executions; ++i) {
                ga::Individual best = ga::runGA(nodes, dm, pop, cr, mr, generations, i, cx);
                total_dist += best.fitness;
              }

              double end_time = omp_get_wtime();
              double avg_dist = total_dist / executions;

              out << instance_name << "," << pop << "," << cr << "," << mr << "," << cx << ","
                  << avg_dist << "," << (end_time - start_time) << "\n";

              std::cout << "  -> " << cx << " Pop: " << pop << " CR: " << cr << " MR: " << mr
                        << " | Avg Dist: " << avg_dist << "\n";
            }
          }
        }
      }
    }

    out.close();
    std::cout << "\n[INFO] All experiments saved to results/experiments.csv\n";
    return 0;
}
