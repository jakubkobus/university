#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define isqrt(n) (int)sqrt(n)

bool isPrime(int n) {
  if(n <= 1)
    return false;
  if(n == 2 || n == 3 || n == 5)
    return true;
  if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
    return false;
  
  int isqrtn = isqrt(n), i = 5;
  while(i <= isqrtn) {
    if(n % i == 0 || n % (i + 2) == 0)
      return false;
    i += 6;
  }

  return true;
}

int main()
{
  int n;

  printf("Podaj liczbe: ");
  scanf("%d", &n);

  printf("%s\n", isPrime(n) ? "TAK" : "NIE");

  return 0;
}