#include <stdio.h>

int main()
{ 
  int a, b, c;

  printf("Podaj: a b\n");
  scanf("%d %d", &a, &b);

  while(b != 0) {
    c = b;
    b = a % b;
    a = c;
  }

  if(a < 0) a *= -1;

  printf("NWD = %d\n", a);

  return 0;
}