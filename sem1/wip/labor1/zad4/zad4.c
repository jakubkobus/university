#include <stdio.h>
#include <math.h>

int main()
{
  float a, b, c, x1, x2;

  printf("Podaj: a b c\n");
  scanf("%f %f %f", &a, &b, &c);

  float delta = (b * b) - (4.0f * a * c);

  if(a == 0.0f)
    printf("Funkcja nie jest kwadratowa\n");
  else if(delta == 0.0f) {
    x1 = (-b) / (2.0f * a);
    printf("x = %f\n", x1);
  } else if(delta > 0) {
    x1 = (-b + sqrt(delta)) / (2.0f * a);
    x2 = (-b - sqrt(delta)) / (2.0f * a);
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
  } else {
    printf("Delta mniejsza od zera\n");
  }
 
  return 0;
}
