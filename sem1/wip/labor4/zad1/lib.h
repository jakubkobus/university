#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void computeSieve(bool *sieve, unsigned n);
unsigned countPrimes(unsigned n);
unsigned nthPrime(unsigned n);
bool isPrime(unsigned n);