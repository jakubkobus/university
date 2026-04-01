#include "my_lib.h"

uint64_t c_GCD(uint64_t a, uint64_t b) {
  while (b != 0) {
    uint64_t temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}

uint64_t c_smallestPrimeFactor(uint64_t n) {
  if (n <= 1) return 0;
  if (n % 2 == 0) return 2;

  for (uint64_t i = 3; i * i <= n; i += 2)
    if (n % i == 0) return i;

  return n;
}

uint64_t c_totient(uint64_t n) {
  if (n == 0) return 0;

  uint64_t result = n;

  for (uint64_t p = 2; p * p <= n; ++p) {
    if (n % p == 0) {
      while (n % p == 0)
        n /= p;

      result -= result / p;
    }
  }

  if (n > 1) result -= result / n;

  return result;
}

static int64_t extendedGCD(int64_t a, int64_t b, int64_t *x, int64_t *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }

  int64_t x1, y1;
  int64_t g = extendedGCD(b % a, a, &x1, &y1);

  *x = y1 - (b / a) * x1;
  *y = x1;

  return g;
}

Solution c_solveDiophantine(uint64_t a_in, uint64_t b_in, uint64_t c_in) {
  Solution sol = { 0, 0, false };
  int64_t a = a_in, b = b_in, c = c_in;

  if (a == 0 && b == 0) {
    if (c == 0)
      sol.hasSolution = true;

    return sol;
  }

  if (a == 0) return sol;

  int64_t x0, y0;
  int64_t g = extendedGCD(a, b, &x0, &y0);

  if (c % g != 0) return sol;

  int64_t a_prime = a / g;
  int64_t b_prime = b / g;
  int64_t c_prime = c / g;

  int64_t x_base = x0 * c_prime;
  int64_t y_temp = y0 * c_prime;
  int64_t y_base = -y_temp;

  int64_t k_x = -x_base / b_prime;
  while (x_base + k_x * b_prime < 0)
    k_x++;

  int64_t k_y = -y_base / a_prime;
  while (y_base + k_y * a_prime < 0)
    k_y++;

  int64_t k = (k_x > k_y) ? k_x : k_y;

  sol.x = (uint64_t)(x_base + k * b_prime);
  sol.y = (uint64_t)(y_base + k * a_prime);
  sol.hasSolution = true;

  return sol;
}
