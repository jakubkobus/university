#include <random>
#include <stdio.h>
#include <limits>
#include <algorithm>

#include "tsp.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <path/to/file.tsp>\n", argv[0]);
    return 1;
  }

  tsp::Route nodes = tsp::load(argv[1]);

  const int PERMUTATIONS = 1000;
  const int INT_MAX = std::numeric_limits<int>::max();
  std::mt19937 rng(std::random_device{}());

  tsp::Route best;
  int bestLen = INT_MAX,
      currLen,
      currGroup10Best = INT_MAX,
      currGroup50Best = INT_MAX;
  long long sumGroup10Best = 0,
            sumGroup50Best = 0;

  for (int i = 1; i <= PERMUTATIONS; i++) {
    shuffle(nodes.begin(), nodes.end(), rng);

    currLen = tsp::calculateLength(nodes);

    if (currLen < currGroup10Best)
      currGroup10Best = currLen;
    if (currLen < currGroup50Best)
      currGroup50Best = currLen;

    if (currLen < bestLen) {
      bestLen = currLen;
      best = nodes;
    }

    if (i % 10 == 0) {
      sumGroup10Best += currGroup10Best;
      currGroup10Best = INT_MAX;
    }

    if (i % 50 == 0) {
      sumGroup50Best += currGroup50Best;
      currGroup50Best = INT_MAX;
    }
  }

  double avgGroup10 = static_cast<double>(sumGroup10Best / (PERMUTATIONS / 10.0)),
         avgGroup50 = static_cast<double>(sumGroup50Best / (PERMUTATIONS / 50.0));

  printf("Srednia z minumum dla kazdych 10 kolejnych losowan: %.2lf\n", avgGroup10);
  printf("Srednia z minumum dla kazdych 50 kolejnych losowan: %.2lf\n", avgGroup50);
  printf("Minimalna wartosc dla 1000 losowan: %d\n", bestLen);

  tsp::saveRoute(best, "best.txt");

  return 0;
}
