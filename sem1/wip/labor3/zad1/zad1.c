#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

void computeSieve(bool sieve[], unsigned n) {
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
    printf("Przekroczono limit pamieci\n");
    exit(EXIT_FAILURE);
  }

  computeSieve(sieve, n);

  for(unsigned i = 2; i <= n; i++)
    if(sieve[i])
      numberOfPrimes++;
  
  free(sieve);
  return numberOfPrimes;
}

int main()
{
  unsigned n;

  printf("Podaj liczbę: ");
  if(scanf("%u", &n) != 1) {
    printf("Dozwolone wartosci w zakresie 2 .. (2^32 - 2)\n");
    return 1;
  }

  if(n > 1 && n < UINT_MAX) {
    printf("Ilosc liczb pierwszych w zakresie 2 .. %u = %u\n", n, countPrimes(n));
  } else {
    printf("Dozwolone wartosci w zakresie 2 .. (2^32 - 2)\n");
  }

  return EXIT_SUCCESS;
}
