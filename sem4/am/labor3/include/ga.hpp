#ifndef GA_HPP
#define GA_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <omp.h>

#include "tsp.hpp"

namespace ga {
  using Route = std::vector<int>;

  struct Individual {
      Route route;
      double fitness;
  };

  class DistanceMatrix {
  private:
    std::vector<std::vector<double>> dist_matrix;
  public:
    DistanceMatrix(const std::vector<tsp::Node>& nodes) {
      size_t n = nodes.size();
      dist_matrix.resize(n, std::vector<double>(n, 0.0));
      for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
          dist_matrix[i][j] = tsp::calculateDistance(nodes[i], nodes[j]);
        }
      }
    }

    double getDistance(int id1, int id2) const {
      return dist_matrix[id1 - 1][id2 - 1];
    }
  };

  double evaluateFitness(const Route& route, const DistanceMatrix& dm) {
    double totalDist = 0;
    for (size_t i = 0; i < route.size() - 1; ++i)
      totalDist += dm.getDistance(route[i], route[i + 1]);
    totalDist += dm.getDistance(route.back(), route.front());
    return totalDist;
  }

  void invertMutation(Route& child, double mutation_rate, std::mt19937& rng) {
    std::uniform_real_distribution<double> chance(0.0, 1.0);
    if (chance(rng) > mutation_rate) return;

    std::uniform_int_distribution<int> dist(0, child.size() - 1);
    int p1 = dist(rng);
    int p2 = dist(rng);
    if (p1 > p2) std::swap(p1, p2);
    std::reverse(child.begin() + p1, child.begin() + p2 + 1);
  }

  Route orderCrossover(const Route& parent1, const Route& parent2, std::mt19937& rng) {
    int size = parent1.size();
    Route child(size, -1);
    std::uniform_int_distribution<int> dist(0, size - 1);

    int start = dist(rng);
    int end = dist(rng);
    if (start > end) std::swap(start, end);

    for (int i = start; i <= end; ++i) child[i] = parent1[i];

    int current_p2 = 0;
    for (int i = 0; i < size; ++i) {
      if (i >= start && i <= end) continue;
      while (std::find(child.begin(), child.end(), parent2[current_p2]) != child.end())
        current_p2++;
      child[i] = parent2[current_p2];
    }

    return child;
  }

  Route pmxCrossover(const Route& parent1, const Route& parent2, std::mt19937& rng) {
    int size = parent1.size();
    Route child(size, -1);
    std::uniform_int_distribution<int> dist(0, size - 1);

    int start = dist(rng);
    int end = dist(rng);
    if (start > end) std::swap(start, end);

    for (int i = start; i <= end; ++i) child[i] = parent1[i];

    for (int i = 0; i < size; ++i) {
      if (i >= start && i <= end) continue;
      int val = parent2[i];
      auto in_segment = [&](int v) {
        return std::find(child.begin() + start, child.begin() + end + 1, v)
                != child.begin() + end + 1;
      };
      while (in_segment(val)) {
        for (int j = start; j <= end; ++j) {
          if (parent1[j] == val) { val = parent2[j]; break; }
        }
      }
      child[i] = val;
    }
    return child;
  }

  int tournamentSelection(const std::vector<Individual>& population, std::mt19937& rng, int k = 3) {
    std::uniform_int_distribution<int> dist(0, population.size() - 1);
    int best_idx = dist(rng);
    for (int i = 1; i < k; ++i) {
      int contender = dist(rng);
      if (population[contender].fitness < population[best_idx].fitness)
        best_idx = contender;
    }
    return best_idx;
  }

  Individual runGA(const std::vector<tsp::Node>& nodes, const DistanceMatrix& dm,
                    int pop_size, double cross_rate, double mut_rate, int generations, int seed,
                    const std::string& cx_type = "OX") {

    std::vector<Individual> population(pop_size);
    Route base_route(nodes.size());
    for (size_t i = 0; i < nodes.size(); ++i) base_route[i] = nodes[i].id;

    #pragma omp parallel
    {
      std::mt19937 local_rng(seed + omp_get_thread_num());
      #pragma omp for
      for (int i = 0; i < pop_size; ++i) {
        population[i].route = base_route;
        std::shuffle(population[i].route.begin(), population[i].route.end(), local_rng);
        population[i].fitness = evaluateFitness(population[i].route, dm);
      }
    }

    for (int gen = 0; gen < generations; ++gen) {
      int elite_idx = 0;
      for (int i = 1; i < pop_size; ++i) {
        if (population[i].fitness < population[elite_idx].fitness)
            elite_idx = i;
      }

      std::vector<Individual> new_population(pop_size);
      new_population[0] = population[elite_idx];

      #pragma omp parallel
      {
        std::mt19937 local_rng(seed + gen + omp_get_thread_num());
        std::uniform_real_distribution<double> chance(0.0, 1.0);

        #pragma omp for
        for (int i = 1; i < pop_size; ++i) {
          int p1_idx = tournamentSelection(population, local_rng);

          if (chance(local_rng) < cross_rate) {
            int p2_idx = tournamentSelection(population, local_rng);
            if (cx_type == "PMX")
              new_population[i].route = pmxCrossover(population[p1_idx].route, population[p2_idx].route, local_rng);
            else
              new_population[i].route = orderCrossover(population[p1_idx].route, population[p2_idx].route, local_rng);
          } else {
            new_population[i].route = population[p1_idx].route;
          }

          invertMutation(new_population[i].route, mut_rate, local_rng);
          new_population[i].fitness = evaluateFitness(new_population[i].route, dm);
        }
      }

      population = new_population;
    }

    int best_idx = 0;
    for (int i = 1; i < pop_size; ++i) {
      if (population[i].fitness < population[best_idx].fitness)
        best_idx = i;
    }

    return population[best_idx];
  }
}
#endif
