#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>

#include "mergeSort.hpp"
#include "mySort.hpp"

std::vector<int> generateRandomArray(int n, std::mt19937 &rng) {
  std::vector<int> arr(n);
  std::uniform_int_distribution<int> dist(1, 1000000);

  for (int i = 0; i < n; i++)
      arr[i] = dist(rng);

  return arr;
}

void saveToCSV(std::ofstream &file, const std::string &algoName, int k, int n, double avgC, double avgS) {
  double c_per_n = avgC / n;
  double s_per_n = avgS / n;
  file << algoName << "," << k << "," << n << "," << avgC << "," << avgS << "," << c_per_n << "," << s_per_n << "\n";
}

int main() {
  std::ofstream file("results.csv");
  if (!file.is_open()) {
    fprintf(stderr, "ERROR: Could not open the file\n");
    return 1;
  }

  file << "algo,k,n,c,s,c_n,s_n\n";

  std::mt19937 rng(std::random_device{}());

  std::vector<int> kValues = { 1, 10, 100 };

  std::vector<int> nValues;
  for (int n = 10; n <= 50; n += 10)
    nValues.push_back(n);
  for (int n = 1000; n <= 50000; n += 1000)
    nValues.push_back(n);

  for (int k : kValues) {
    printf("Testing k=%d...\n", k);

    for (int n : nValues) {
      unsigned long long total_c_merge = 0, total_s_merge = 0;
      unsigned long long total_c_my = 0,    total_s_my = 0;

      for (int i = 0; i < k; i++) {
        std::vector<int> original_arr = generateRandomArray(n, rng);

        std::vector<int> arr_merge = original_arr;
        unsigned long long c_merge = 0;
        unsigned long long s_merge = 0;
        mergeSort(arr_merge, c_merge, s_merge);
        total_c_merge += c_merge;
        total_s_merge += s_merge;

        std::vector<int> arr_my = original_arr;
        unsigned long long c_my = 0;
        unsigned long long s_my = 0;
        mySort(arr_my, c_my, s_my);
        total_c_my += c_my;
        total_s_my += s_my;
      }

      double avg_c_merge = (double)total_c_merge / k;
      double avg_s_merge = (double)total_s_merge / k;

      double avg_c_my = (double)total_c_my / k;
      double avg_s_my = (double)total_s_my / k;

      saveToCSV(file, "MergeSort", k, n, avg_c_merge, avg_s_merge);
      saveToCSV(file, "MySort",    k, n, avg_c_my,    avg_s_my);
    }
  }

  file.close();

  return 0;
}
