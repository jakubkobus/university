#include "lib.h"

void primeFactors(unsigned factors[], unsigned *size) {
  unsigned t = 3, n = *size;
  *size = 0;

  while(n % 2 == 0) {
    factors[(*size)++] = 2;
    n /= 2;
  }

  while(n > 1) {
    if(t * t > n) {
      factors[(*size)++] = n;
      n = 1;
    } else {
      while(n % t == 0) {
        factors[(*size)++] = t;
        n /= t;
      }

      t += 2;
    }
  }
}

unsigned totient(unsigned n) {
  if(n == 1) return 1;

  unsigned factors[(int)log2(n)], size = n;
  primeFactors(factors, &size);

  unsigned result = n - (n / factors[0]);
  for(unsigned i = 1; i < size; i++) {
    if(factors[i] != factors[i - 1])
      result -= result / factors[i];
  }

  return result;
}
