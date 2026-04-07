#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

#include "matrixSearch.hpp"

using namespace std;

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

int main() {
  ofstream csv("results.csv");
  csv << "shape,m,n,algo,comparisons\n";

  std::mt19937 rng(std::random_device{}());

  int k = 50;

  vector<pair<size_t, size_t>> shapes = {
    { 2, 500000 }, { 10, 100000 }, { 100, 10000 },
    { 1000, 1000 },
    { 10000, 100 }, { 100000, 10 }, { 500000, 2 }
  };

  printf("Rectangles k=%d...\n", k);
  for (auto [m, n] : shapes) {
    Matrix mat = generateRandomMatrix(m, n, rng);

    std::uniform_int_distribution<size_t> row_dist(0, m - 1);
    std::uniform_int_distribution<size_t> col_dist(0, n - 1);

    long long binSum = 0, sadSum = 0, hybSum = 0;

    for(int i = 0; i < k; i++) {
      int target = mat[row_dist(rng)][col_dist(rng)];

      binSum += binarySearch(mat, target).comparisons;
      sadSum += saddlebackSearch(mat, target).comparisons;
      hybSum += hybridSearch(mat, target).second.comparisons;
    }

    csv << "Rectangle," << m << "," << n << ",Binary," << binSum / k << "\n";
    csv << "Rectangle," << m << "," << n << ",Saddleback," << sadSum / k << "\n";
    csv << "Rectangle," << m << "," << n << ",Hybrid," << hybSum / k << "\n";
  }

  vector<size_t> sizes = { 100, 250, 500, 1000, 2000, 5000, 10000, 25000, 50000 };

  printf("Squares k=%d...\n", k);
  for (size_t s : sizes) {
    Matrix mat = generateRandomMatrix(s, s, rng);

    std::uniform_int_distribution<size_t> row_dist(0, s - 1);
    std::uniform_int_distribution<size_t> col_dist(0, s - 1);

    long long binSum = 0, sadSum = 0, hybSum = 0;

    for(int i = 0; i < k; ++i) {
      int target = mat[row_dist(rng)][col_dist(rng)];

      binSum += binarySearch(mat, target).comparisons;
      sadSum += saddlebackSearch(mat, target).comparisons;
      hybSum += hybridSearch(mat, target).second.comparisons;
    }

    csv << "Square," << s << "," << s << ",Binary," << binSum / k << "\n";
    csv << "Square," << s << "," << s << ",Saddleback," << sadSum / k << "\n";
    csv << "Square," << s << "," << s << ",Hybrid," << hybSum / k << "\n";
  }

  csv.close();
  return 0;
}
