#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint64_t x;
  uint64_t y;
  bool hasSolution;
} Solution;

extern void adainit(void);
extern void adafinal(void);

extern uint64_t c_GCD(uint64_t a, uint64_t b);
extern uint64_t c_smallestPrimeFactor(uint64_t n);
extern uint64_t c_totient(uint64_t n);
extern Solution c_solveDiophantine(uint64_t a, uint64_t b, uint64_t c);

extern uint64_t ada_GCD(uint64_t a, uint64_t b);
extern uint64_t ada_smallestPrimeFactor(uint64_t n);
extern uint64_t ada_totient(uint64_t n);
extern Solution ada_solveDiophantine(uint64_t a, uint64_t b, uint64_t c);

extern uint64_t rust_GCD(uint64_t a, uint64_t b);
extern uint64_t rust_smallestPrimeFactor(uint64_t n);
extern uint64_t rust_totient(uint64_t n);
extern Solution rust_solveDiophantine(uint64_t a, uint64_t b, uint64_t c);

#endif // WRAPPER_H
