#include <inttypes.h>
#include <stdio.h>

#include "my_lib.h"

int main() {
  printf("1. GCD(48, 18) = %lu\n", c_GCD(48, 18));
  printf("2. smallestPrimeFactor(15) = %lu\n",
         c_smallestPrimeFactor(15));
  printf("3. totient(12) = %lu\n", c_totient(12));

  uint64_t a = 21, b = 3, c = 15;
  Solution sol = c_solveDiophantine(a, b, c);

  if (sol.hasSolution)
    printf("4. %lux - %luy = %lu -> x = %lu, y = %lu\n", a, b, c, sol.x, sol.y);
  else
    printf("4. No solution for solveDiophantine(a = %lu, b = %lu, c = %lu)\n", a, b, c);

  return 0;
}
