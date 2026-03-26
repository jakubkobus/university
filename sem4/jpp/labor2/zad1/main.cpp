#include <cstdio>
#include <exception>

#include "ring.hpp"

int main() {
  try {
    printf("--- Z7 (Ring<7>) ---\n");
    printf("[IN] a = 10, b = -4\n");
    Ring<7> a = 10;
    Ring<7> b = -4;

    printf("a = %lld\nb = %lld\n", a.get(), b.get());
    printf("a == b -> %s\n", (a == b ? "true" : "false"));

    printf("a + b = %lld\n", (a + b).get());

    printf("a * 5 = %lld\n", (a * 5).get());

    printf("a / 2 = %lld\n", (a / 2).get());

    printf("a ^ 2 = %lld\n", (a * a).get());

    printf("\n--- Z6 (Ring<6>) ---\n");
    printf("[IN] x = 5, y = 2\n");
    Ring<6> x = 5;
    Ring<6> y = 2;

    printf("x = %lld\ny = %lld\n", x.get(), y.get());
    printf("x * y = %lld\n", (x * y).get());

    printf("\nException handling:\n");

    printf("\nDividing x / y ...\n");
    Ring<6> _ = x / y;
  } catch (const std::exception &exc) {
    fprintf(stderr, "[WARN] Exception catched: %s\n", exc.what());
  }

  try {
    printf("\nDividing by zero...\n");
    Ring<7> _ = Ring<7>(5) / Ring<7>();
  } catch (const std::exception &exc) {
    fprintf(stderr, "[WARN] Exception catched: %s\n", exc.what());
  }

  return 0;
}
