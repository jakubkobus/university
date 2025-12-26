#include <stdio.h>

#define min(a, b) (a < b) ? a : b

unsigned binomialCoefficient(unsigned n, unsigned k) {
  unsigned min_, i, j;

  k = min(k, n - k);
  if(k == 0) return 1;

  unsigned arr[k + 1];
  arr[0] = 1;

  for(i = 1; i <= n; i++) {
    if(i <= k) {
      min_ = i - 1;
      arr[i] = 1;
    } else min_ = k;

    for(j = min_; j > 0; j--)
      arr[j] += arr[j - 1];
  } 

  return arr[k];
}

int main()
{
  unsigned n, k;

  printf("Podaj: n k\n");
  scanf("%u %u", &n, &k);
  printf("Dwumian(%u, %u) = %u\n", n, k, binomialCoefficient(n, k));

  return 0;
}