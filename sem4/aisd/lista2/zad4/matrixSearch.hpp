#ifndef MATRIX_SEARCH_HPP
#define MATRIX_SEARCH_HPP

#include <cmath>
#include <vector>
#include <cstdio>
#include <string>

typedef std::vector<std::vector<int>> Matrix;

struct SearchResult {
  bool found;
  size_t comparisons;
};

inline SearchResult binarySearch(const Matrix &matrix, const int target) {
  const size_t HEIGHT = matrix.size(),
               WIDTH  = matrix[0].size();

  size_t comparisons = 0;

  if (HEIGHT <= WIDTH) {
    for (size_t i = 0; i < HEIGHT; i++) {
      int left  = 0,
          right = WIDTH - 1;

      while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;

        if (matrix[i][mid] == target)
          return { true, comparisons };

        comparisons++;
        if (matrix[i][mid] < target)
          left = mid + 1;
        else
          right = mid - 1;
      }
    }
  } else {
    for (size_t j = 0; j < WIDTH; j++) {
      int top    = 0,
          bottom = HEIGHT - 1;

      while (top <= bottom) {
        comparisons++;
        int mid = top + (bottom - top) / 2;

        if (matrix[mid][j] == target)
          return { true, comparisons };

        comparisons++;
        if (matrix[mid][j] < target)
          top = mid + 1;
        else
          bottom = mid - 1;
      }
    }
  }

  return { false, comparisons };
}

inline SearchResult saddlebackSearch(const Matrix &matrix, const int target) {
  const size_t HEIGHT = matrix.size(),
               WIDTH  = matrix[0].size();

  size_t comparisons = 0;

  int row = 0,
      col = WIDTH - 1;

  while (row < static_cast<int>(HEIGHT) && col >= 0) {
    comparisons++;
    if (matrix[row][col] == target)
      return { true, comparisons };

    comparisons++;
    if (matrix[row][col] > target)
      col--;
    else
      row++;
  }

  return { false, comparisons };
}

inline std::pair<std::string, SearchResult> hybridSearch(const Matrix &matrix, const int target) {
  const size_t HEIGHT = matrix.size(),
               WIDTH  = matrix[0].size();

  const double saddlebackCost = WIDTH + HEIGHT,
               binaryCost = std::min(WIDTH, HEIGHT) * log2(static_cast<double>(std::max(WIDTH, HEIGHT)));

  if (saddlebackCost < binaryCost)
    return { "saddleback", saddlebackSearch(matrix, target) };
  else
    return { "binary", binarySearch(matrix, target) };
}

#endif // MATRIX_SEARCH_HPP
