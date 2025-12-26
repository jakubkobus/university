#include <stdio.h>
#include <stdlib.h>

unsigned NWD(int a, int b) {
  int c;

  while(b != 0) {
    c = b;
    b = a % b;
    a = c;
  }

  return abs(a);
}

int main()
{ 
  int a, b;

  printf("Podaj: a b\n");
  scanf("%d %d", &a, &b);

  printf("NWD = %u\n", NWD(a, b));

  return 0;
}