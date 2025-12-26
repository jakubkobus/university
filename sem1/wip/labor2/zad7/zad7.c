#include <stdio.h>
#include <math.h>

#define log2i(n) (int)log2(n)

int main()
{
  unsigned n, t = 3, i = 0;
  
  printf("Podaj liczbe: ");
  scanf("%u", &n);

  unsigned result[log2i(n)];
  printf("%d=", n);

  while(n % 2 == 0) {
    result[i++] = 2;
    n /= 2;
  }

  while(n > 1) {
    if(t * t > n) {
      result[i++] = n;
      n = 1;
    } else {
      while(n % t == 0) {
        result[i++] = t;
        n /= t;
      }

      t += 2;
    }
  }

  n = result[0];
  t = 1;

  for(size_t j = 1; j < i; j++) {
    if(result[j] == n) t++;
    else {
      if(t == 1) printf("%d*", n);
      else printf("%d^%d*", n, t);

      n = result[j];
      t = 1;
    }
  }

  if(t == 1) printf("%d\n", n);
  else       printf("%d^%d\n", n, t);

  return 0;
}