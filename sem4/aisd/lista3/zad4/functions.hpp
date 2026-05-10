#pragma once

#include <math.h>

inline double fun1(int x) {
  double l = log2(x + 1.0);
  return l * l * l;
}

inline int inverseFun1(double y) {
  if (y < 0) return 0;
  return std::max(0, static_cast<int>(floor(pow(2.0, cbrt(y)) - 1)));
}

inline double fun2(int x) {
  return sqrt(x) + log2(x + 1.0);
}
