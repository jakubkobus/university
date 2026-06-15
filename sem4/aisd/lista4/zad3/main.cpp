#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>

#include "include/SplayTree.hpp"

int main() {
  const int N = 30;

  std::mt19937_64 rng(std::random_device{}());
  SplayTree tree;
  Stats dummy;

  std::vector<int> perm(N);
  for(short i = 0; i < N; i++)
    perm[i] = i + 1;
  shuffle(perm.begin(), perm.end(), rng);

  // pkt 1
  for(short i = 0; i < N; i++) {
    printf("insert %d\n", i + 1);
    tree.insertNode(i + 1, dummy);
    tree.print();
  }

  for(short i = 0; i < N; i++) {
    printf("delete %d\n", perm[i]);
    tree.deleteKey(perm[i], dummy);
    tree.print();
  }

  // pkt 2
  shuffle(perm.begin(), perm.end(), rng);
  for(short i = 0; i < N; i++) {
    printf("insert %d\n", perm[i]);
    tree.insertNode(perm[i], dummy);
    tree.print();
  }

  shuffle(perm.begin(), perm.end(), rng);
  for(short i = 0; i < N; i++) {
    printf("delete %d\n", perm[i]);
    tree.deleteKey(perm[i], dummy);
    tree.print();
  }

  return 0;
}
