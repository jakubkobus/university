#include <stdio.h>

int main()
{
  int n, p, t, m;

  printf("Podaj: n p\n");
  scanf("%d %d", &n, &p);

  t = n;
  m = 0;

  while(t >= 1) {
    m = m * p + (t % p);
    t /= p;
  }

  if(m == n) printf("TAK\n");
  else printf("NIE\n");

  return 0;
}