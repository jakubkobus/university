#include <stdio.h>

#include "wrapper.h"

int main() {
  adainit();

  uint64_t a, b, c;
  Solution sol;

  a = 48; b = 18;
  printf("NWD(%lu, %lu)\n", a, b);
  printf("C    -> %lu\n", c_GCD(a, b));
  printf("Ada  -> %lu\n", ada_GCD(a, b));
  printf("Rust -> %lu\n\n", rust_GCD(a, b));

  a = 15;
  printf("smallestPrimeFactor(%lu)\n", a);
  printf("C    -> %lu\n", c_smallestPrimeFactor(a));
  printf("Ada  -> %lu\n", ada_smallestPrimeFactor(a));
  printf("Rust -> %lu\n\n", rust_smallestPrimeFactor(a));

  a = 12;
  printf("totient(%lu)\n", a);
  printf("C    -> %lu\n", c_totient(a));
  printf("Ada  -> %lu\n", ada_totient(a));
  printf("Rust -> %lu\n\n", rust_totient(a));

  a = 21; b = 3; c = 15;
  printf("solveDiophantine(%lu, %lu, %lu)\n", a, b, c);

  sol = c_solveDiophantine(a, b, c);
  printf("C    -> x = %lu, y = %lu, hasSolution -> %s\n",
          sol.x, sol.y, sol.hasSolution ? "true" : "false");

  sol = ada_solveDiophantine(a, b, c);
  printf("Ada  -> x = %lu, y = %lu, hasSolution -> %s\n",
          sol.x, sol.y, sol.hasSolution ? "true" : "false");

  sol = rust_solveDiophantine(a, b, c);
  printf("Rust -> x = %lu, y = %lu, hasSolution -> %s\n",
          sol.x, sol.y, sol.hasSolution ? "true" : "false");

  adafinal();
  return 0;
}
