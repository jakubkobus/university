#ifndef MY_LIB_H
#define MY_LIB_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint64_t x;
    uint64_t y;
    bool hasSolution;
} Solution;

uint64_t c_GCD(uint64_t a, uint64_t b);
uint64_t c_smallestPrimeFactor(uint64_t n);
uint64_t c_totient(uint64_t n);
Solution c_solveDiophantine(uint64_t a, uint64_t b, uint64_t c);

#endif // MY_LIB_H
