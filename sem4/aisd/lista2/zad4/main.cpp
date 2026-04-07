#include <cstdio>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

#include "matrixSearch.hpp"

void printMatrix(const Matrix &matrix) {
  for (size_t row = 0; row < matrix.size(); row++) {
    for (size_t col = 0; col < matrix[0].size(); col++) {
      printf("%4d ", matrix[row][col]);
    }
    printf("\n");
  }
}

Matrix generateRandomMatrix(size_t height, size_t width, std::mt19937 &rng) {
  Matrix matrix(height, std::vector<int>(width));
  std::uniform_int_distribution<int> dist(1, 5);

  matrix[0][0] = dist(rng) * 2;

  for (size_t col = 1; col < width; col++) {
    matrix[0][col] = matrix[0][col - 1] + (dist(rng) * 2);
  }

  for (size_t row = 1; row < height; row++) {
    matrix[row][0] = matrix[row - 1][0] + (dist(rng) * 2);
  }

  for (size_t row = 1; row < height; row++) {
    for (size_t col = 1; col < width; col++) {
      int maxNeighbor = std::max(matrix[row - 1][col], matrix[row][col - 1]);
      matrix[row][col] = maxNeighbor + (dist(rng) * 2);
    }
  }

  return matrix;
}

void runExperiment(size_t m, size_t n, std::mt19937 &rng) {
  Matrix matrix = generateRandomMatrix(m, n, rng);
  std::uniform_int_distribution<int> distM(0, m - 1);
  std::uniform_int_distribution<int> distN(0, n - 1);

  int target = matrix[distM(rng)][distN(rng)];

  SearchResult resBin = binarySearch(matrix, target);
  SearchResult resSad = saddlebackSearch(matrix, target);
  auto resHyb = hybridSearch(matrix, target);

  printf("Dimensions: %6zu x %-6zu | Size: %zu elements\n", m, n, (m * n));
  printf("  Binary Search:      %-7zu comparisons\n", resBin.comparisons);
  printf("  Saddleback:         %-7zu comparisons\n", resSad.comparisons);
  printf("  Winner:             %s\n",
          (resBin.comparisons < resSad.comparisons ? "Binary Search" : "Saddleback Search"));
  printf("  hybridSort choice:  %s (%zu comparisons)\n\n",
          resHyb.first.c_str(), resHyb.second.comparisons);
}

int main() {
  std::mt19937 rng(std::random_device{}());

  runExperiment(1000, 1000, rng);
  runExperiment(100, 10000, rng);
  runExperiment(10, 100000, rng);
  runExperiment(2, 500000, rng);
  runExperiment(500000, 2, rng);
  runExperiment(100000, 10, rng);
  runExperiment(10000, 100, rng);

  return 0;
}
