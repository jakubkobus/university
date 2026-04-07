#include <algorithm>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

int throwUsage(const std::string name) {
  fprintf(stderr, "Usage: %s <n> <rand|asc|desc>\n", name.c_str());
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    return throwUsage(argv[0]);

  std::mt19937 rng(std::random_device{}());

  int n = atoi(argv[1]);
  std::string type = argv[2];
  std::vector<int> data(n);
  std::uniform_int_distribution<int> dist(0, 2 * n - 1);

  for (int i = 0; i < n; i++)
    data[i] = dist(rng);

  if (type == "asc")
    sort(data.begin(), data.end());
  else if (type == "desc")
    sort(data.rbegin(), data.rend());
  else if (type != "rand")
    return throwUsage(argv[0]);

  printf("%d\n", n);
  for (int i = 0; i < n; i++)
    printf("%d%c", data[i], (i == n - 1) ? '\n' : ' ');

  return 0;
}
