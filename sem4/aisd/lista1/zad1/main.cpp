#include <stdio.h>

#include "fifo.hpp"
#include "lifo.hpp"

int main() {
  const bool DEBUG = true;

  printf("--- FIFO ---\n");

  FIFO fifo(50, DEBUG);

  for (int i = 1; i < 52; i++)
    fifo.push(i);

  printf("\n");

  for (int i = 1; i < 52; i++)
    fifo.pop();

  printf("\n\n--- LIFO ---\n");

  LIFO lifo(50, DEBUG);

  for (int i = 1; i < 52; i++)
    lifo.push(i);

  printf("\n");

  for (int i = 1; i < 52; i++)
    lifo.pop();

  return 0;
}
