#include <stdio.h>
#include <math.h>

typedef double (*function_t)(double);

double myFun(double x) {
  return cos(x / 2);
}

double findZero(function_t f, double a, double b, double eps) {
  double mid;

  while((b - a) / 2 > eps) {
    mid = (a + b) / 2;

    if(f(mid) == 0.0) 
      return mid;
    else if(f(a) * f(mid) < 0) 
      b = mid;
    else
      a = mid;
  }

  return (a + b) / 2;
}

int main() {
  double epsilon[] = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8 };
  int epsilonSize = sizeof(epsilon) / sizeof(epsilon[0]);
  double a = 2.0, b = 4.0;

  for(size_t i = 0; i < epsilonSize; i++)
    printf(
      "x0 = %.*lf : epsilon = %.*lf\n",
      epsilonSize + 1,
      findZero(myFun, a, b, epsilon[i]),
      (int)(i + 1),
      epsilon[i]
    );

  return 0;
}
