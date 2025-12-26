#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define isqrt(n) (int)sqrt(n)

unsigned nthPrime(unsigned n) {
  if(n < 1) return 0;

  unsigned primes[n], candidate = 3, iterator = 1, i, s;
  bool isPrime;

  primes[0] = 2;

  while(iterator < n) {
    s = isqrt(candidate);
    isPrime = true;
    i = 1;

    while(isPrime && primes[i] <= s && i < iterator)
      if(candidate % primes[i++] == 0) isPrime = false;

    if(isPrime)
      primes[iterator++] = candidate;
    
    candidate += 2;
  }

  return primes[n - 1];
}

int main()
{
  unsigned n;

  printf("Podaj n: ");
  scanf("%u", &n);

  printf("%u liczba pierwsza = %u\n", n, nthPrime(n));

  return 0;
}
