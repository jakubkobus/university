#include <fstream>
#include <iostream>
#include <random>

void simulateTimeFraction(int n, int k, const std::string &filename);

int main() {
  const int nValues[] = { 100, 1000, 10000 };
  const int k = 5000;

  for(auto n : nValues) {
    std::string filename = "results/task3_n" + std::to_string(n) + ".csv";
    simulateTimeFraction(n, k, filename);
  }

  return 0;
}

void simulateTimeFraction(int n, int k, const std::string &filename) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 1);

  std::ofstream file(filename);
  file << "Pn\n";

  int i, step, currSn, prevSn, Ln;
  for(i = 0; i < k; i++) {
    currSn = 0;
    prevSn = 0;
    Ln = 0;

    for(step = 1; step <= n; step++) {
      prevSn = currSn;

      currSn += (dis(gen) == 1) ? 1 : -1;

      if(currSn > 0 || prevSn > 0)
        Ln++;
    }

    file << (double)Ln / n << "\n";
  }

  file.close();
}