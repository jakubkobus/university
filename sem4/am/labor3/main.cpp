#include <iostream>
#include <iomanip>
#include <chrono>
#include <filesystem>
#include <omp.h>

#include "include/tsp.hpp"
#include "include/ga.hpp"

int main() {
  const int POP_SIZE = 200;
  const double CROSS_RATE = 0.7;
  const double MUT_RATE = 0.1;
  const int GENERATIONS = 1500;
  const int EXECUTIONS = 10;
  const std::string CX_TYPE = "OX";

  std::vector<std::string> tsp_files;
  for (const auto& entry : std::filesystem::directory_iterator("data"))
    if (entry.path().extension() == ".tsp")
      tsp_files.push_back(entry.path().string());
  std::sort(tsp_files.begin(), tsp_files.end());

  std::cout << "[INFO] Max OpenMP Threads: " << omp_get_max_threads() << "\n";
  std::cout << "[INFO] pop=" << POP_SIZE << " cr=" << CROSS_RATE
            << " mr=" << MUT_RATE << " gens=" << GENERATIONS
            << " cx=" << CX_TYPE << " exec=" << EXECUTIONS << "\n\n";

  std::cout << std::left << std::setw(12) << "Instance"
            << std::setw(10) << "Nodes"
            << std::setw(18) << "Avg Distance"
            << std::setw(18) << "Best Distance"
            << std::setw(14) << "Time (s)" << "\n";
  std::cout << std::string(72, '-') << "\n";

  for (const auto& filename : tsp_files) {
    std::string name = std::filesystem::path(filename).stem().string();
    auto nodes = tsp::load(filename);
    ga::DistanceMatrix dm(nodes);

    double total_dist = 0, best_dist = std::numeric_limits<double>::max();
    ga::Individual best_ind;
    auto t0 = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:total_dist) schedule(dynamic)
    for (int i = 0; i < EXECUTIONS; ++i) {
      ga::Individual ind = ga::runGA(nodes, dm, POP_SIZE, CROSS_RATE,
                                      MUT_RATE, GENERATIONS, i, CX_TYPE);
      total_dist += ind.fitness;
      #pragma omp critical
      if (ind.fitness < best_dist) {
        best_dist = ind.fitness;
        best_ind = ind;
      }
    }

    auto t1 = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(t1 - t0).count();

    std::cout << std::left << std::setw(12) << name
              << std::setw(10) << nodes.size()
              << std::setw(18) << std::fixed << std::setprecision(2) << (total_dist / EXECUTIONS)
              << std::setw(18) << best_dist
              << std::setw(14) << elapsed << "\n";

    tsp::Route final_route;
    for (int id : best_ind.route)
      final_route.push_back(nodes[id - 1]);

    std::filesystem::create_directories("results/txt");
    tsp::saveRoute(final_route, "results/txt/route_" + name + ".txt");
  }

  return 0;
}
