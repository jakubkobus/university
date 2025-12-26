#include "lib.h"

void computeSieve(bool *sieve, unsigned n) {
  unsigned i, j;

  for(i = 2; i <= n; i++)
    sieve[i] = true;

  for(i = 2; i <= n; i++)
    if(sieve[i]) {
      j = i + i;
      while(j <= n) {
        sieve[j] = false;
        j += i;
      }
    }
}

unsigned countPrimes(unsigned n) {
  bool *sieve = malloc((n + 1) * sizeof(bool));
  unsigned numberOfPrimes = 0;

  if(sieve == NULL) {
    perror("Przekroczono limit pamieci\n");
    exit(1);
  }

  computeSieve(sieve, n);

  for(unsigned i = 2; i <= n; i++)
    if(sieve[i])
      numberOfPrimes++;
  
  free(sieve);
  return numberOfPrimes;
}

unsigned nthPrime(unsigned n) {
  if(n < 1) return 0;

  unsigned primes[n], candidate = 3, iterator = 1, i, s;
  bool isPrime;

  primes[0] = 2;

  while(iterator < n) {
    s = (int)sqrt(candidate);
    isPrime = true;
    i = 1;

    while(isPrime && primes[i] <= s && i < iterator) {
      if(candidate % primes[i] == 0) isPrime = false;
      else i++;
    }

    if(isPrime)
      primes[iterator++] = candidate;
    
    candidate += 2;
  }

  return primes[n - 1];
}

bool isPrime(unsigned n) {
  if(n <= 1)
    return false;
  if(n == 2 || n == 3 || n == 5)
    return true;
  if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
    return false;
  
  unsigned isqrtn = (int)sqrt(n), i = 5;
  while(i <= isqrtn) {
    if(n % i == 0 || n % (i + 2) == 0)
      return false;
    i += 6;
  }

  return true;
}