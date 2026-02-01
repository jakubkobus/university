#include <iostream>
#include <fstream>
#include <random>

void simulateSn(int n, int k, const std::string &filename);

int main() {
  const int nValues[] = { 5, 10, 15, 20, 25, 30, 100 };
  const int k = 100000;

  for(auto n : nValues) {
    std::string filename = "results/task2_n" + std::to_string(n) + ".csv";
    simulateSn(n, k, filename);
  }

  return 0;
}

void simulateSn(int n, int k, const std::string &filename) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 1);

  std::ofstream file(filename);
  file << "Sn\n";

  int i, j, Sn;
  for(i = 0; i < k; i++) {
    Sn = 0;

    for(j = 0; j < n; j++)
      Sn += (dis(gen) == 1) ? 1 : -1;

    file << Sn << "\n";
  }

  file.close();
}