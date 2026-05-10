#include <stdio.h>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <fstream>

#include "functions.hpp"

bool mySearchFun1(const std::vector<double> &A, const double q, const double delta, int &comparisons, bool print = false);
int findIndexFun2(const int n, const double target);
bool mySearchFun2(const std::vector<double> &A, const double q, const double delta, int &comparisons, bool print = false);

bool binarySearch(const std::vector<double> &A, const double q, int &comparisons);

int main(int argc, char *argv[]) {
  if (argc == 2) {
    int n = atoi(argv[1]);

    if (n <= 0 || n > 50)
      return 1;

    std::mt19937 rng1(std::random_device{}());
    std::uniform_int_distribution<int> distIdx(0, n - 1);

    printf("\n--- Funkcja 1 ---\n");
    std::vector<double> A1(n);
    std::uniform_real_distribution<double> dist1(0, 10.0);
    for (int i = 0; i < n; i++)
      A1[i] = fun1(i) + dist1(rng1) * 0.999;
    std::sort(A1.begin(), A1.end());

    double q1 = A1[distIdx(rng1)];

    printf("Tablica A1:\n[ ");
    for (int i = 0; i < n; i++) printf("%.2f ", A1[i]);
    printf("]\n\nSzukana: %.2f\n", q1);

    int cmp1 = 0;
    mySearchFun1(A1, q1, 10.0, cmp1, true);
    printf("[MySearch] Porownania: %d\n", cmp1);
    cmp1 = 0;
    binarySearch(A1, q1, cmp1);
    printf("[Binary Search] Porownania: %d\n", cmp1);

    printf("\n--- Funkcja 2 ---\n");
    std::vector<double> A2(n);
    std::uniform_real_distribution<double> dist2(0, 50.0);
    for (int i = 0; i < n; i++)
      A2[i] = fun2(i) + dist2(rng1) * 0.999;
    std::sort(A2.begin(), A2.end());

    double q2 = A2[distIdx(rng1)];

    printf("Tablica A2:\n[ ");
    for (int i = 0; i < n; i++) printf("%.2f ", A2[i]);
    printf("]\n\nSzukana: %.2f\n", q2);

    int cmp2 = 0;
    mySearchFun2(A2, q2, 50.0, cmp2, true);
    printf("[MySearch] Porownania: %d\n", cmp2);
    cmp2 = 0;
    binarySearch(A1, q2, cmp2);
    printf("[Binary Search] Porownania: %d\n", cmp2);

    return 0;
  }

  const std::string FILENAME = "task4_results.csv";
  std::ofstream file(FILENAME);
  file << "n,fun,binarySearch,mySearch\n";

  std::mt19937 rng(std::random_device{}());

  for (int n = 1000; n <= 300000; n += 1000) {
    if (n % 50000 == 0)
      printf("Processing n = %d ...\n", n);

    std::vector<double> A1(n);
    std::uniform_real_distribution<double> dist1(0, 10.0);
    for (int i = 0; i < n; i++)
      A1[i] = fun1(i) + dist1(rng) * 0.999;
    std::sort(A1.begin(), A1.end());

    double q = A1[n / 2];
    int bsComparisons = 0;
    int msComparisons = 0;

    binarySearch(A1, q, bsComparisons);
    mySearchFun1(A1, q, 10.0, msComparisons);

    file << n << ",f1," << bsComparisons << "," << msComparisons << "\n";

    std::vector<double> A2(n);
    std::uniform_real_distribution<double> dist2(0, 50.0);
    for (int i = 0; i < n; i++)
      A2[i] = fun2(i) + dist2(rng) * 0.999;
    std::sort(A2.begin(), A2.end());

    q = A2[n / 2];
    bsComparisons = 0;
    msComparisons = 0;

    binarySearch(A2, q, bsComparisons);
    mySearchFun2(A2, q, 50.0, msComparisons);

    file << n << ",f2," << bsComparisons << "," << msComparisons << "\n";
  }

  file.close();
  printf("Results saved to '%s'\n", FILENAME.c_str());

  return 0;
}

bool mySearchFun1(const std::vector<double> &A, const double q, const double delta, int &comparisons, bool print) {
  int n = A.size();
  int left = inverseFun1(q - delta);
  int mid;
  int right = std::min(
    n - 1,
    static_cast<int>(ceil(pow(2.0, cbrt(q)) - 1) + 1)
  );

  int currLeft  = std::max(0, left);
  int currRight = std::min(n - 1, right);

  if (print)
    printf("[Funkcja 1] Wyliczono przedzial wyszukiwan: L = %d, R = %d\n", currLeft, currRight);

  while (currLeft <= currRight) {
    mid = currLeft + (currRight - currLeft) / 2;

    comparisons++;
    if (A[mid] == q) {
      if (print)
        printf("[Funkcja 1] TAK (index = %d)\n", mid);

      return true;
    }

    comparisons++;
    if (A[mid] < q) currLeft = mid + 1;
    else currRight = mid - 1;
  }

  if (print)
    printf("[Funkcja 1] NIE\n");

  return false;
}

int findIndexFun2(const int n, const double target) {
  int left = 0;
  int mid;
  int right = n - 1;
  int res = left;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (fun2(mid) <= target) {
      res = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return res;
}

bool mySearchFun2(const std::vector<double> &A, const double q, const double delta, int &comparisons, bool print) {
  int n = A.size();
  int left = findIndexFun2(n, q - delta);
  int currLeft = 0;
  int currRight = n - 1;
  int right = currRight;
  int mid;

  while (currLeft <= currRight) {
    mid = currLeft + (currRight - currLeft) / 2;

    if (fun2(mid) > q) {
      right = mid;
      currRight = mid - 1;
    } else {
      currLeft = mid + 1;
    }
  }

  left = std::max(0, left);
  right = std::min(n - 1, right + 1);

  if (print)
    printf("[Funkcja 2] Ograniczono przedzial: L = %d, R = %d\n", left, right);

  while (left <= right) {
    mid = left + (right - left) / 2;

    comparisons++;
    if (A[mid] == q) {
      if (print)
        printf("[Funkcja 2] TAK (index = %d)\n", mid);

      return true;
    }

    comparisons++;
    if (A[mid] < q)
      left = mid + 1;
    else
      right = mid - 1;
  }

  if (print)
    printf("[Funkcja 2] NIE\n");

  return false;
}

bool binarySearch(const std::vector<double> &A, const double q, int &comparisons) {
  int left = 0;
  int mid;
  int right = A.size() - 1;

  while (left <= right) {
    mid = left + (right - left) / 2;

    comparisons++;
    if (A[mid] == q)
      return true;

    comparisons++;
    if (A[mid] < q)
      left = mid + 1;
    else
      right = mid - 1;
    }

  return false;
}
