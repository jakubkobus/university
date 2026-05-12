#ifndef DH_HPP
#define DH_HPP

#include <vector>
#include <random>

#include "ring.hpp"

template <typename T>
class DHSetup {
private:
  T generator;

  std::vector<ll_t> getPrimeFactors(ll_t n) const {
    std::vector<ll_t> factors;

    for (ll_t i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        factors.push_back(i);
        while (n % i == 0)
          n /= i;
      }
    }

    if (n > 1)
      factors.push_back(n);

    return factors;
  }

public:
  DHSetup() {
    ll_t p = T::MOD;
    std::vector<ll_t> factors = getPrimeFactors(p - 1);

    std::mt19937_64 gen(std::random_device{}());
    std::uniform_int_distribution<ll_t> dist(1, p - 1);

    while (true) {
      ll_t a = dist(gen);
      T candidate(a);
      bool isGenerator = true;

      for (ll_t q : factors) {
        if (power(candidate, (p - 1) / q) == T(1)) {
          isGenerator = false;
          break;
        }
      }

      if (isGenerator) {
        generator = candidate;
        break;
      }
    }
  }

  ~DHSetup() = default;

  T getGenerator() const {
    return generator;
  }

  T power(T a, unsigned long b) const {
    T result(1);

    while (b > 0) {
      if (b % 2 == 1)
        result *= a;
      a *= a;
      b /= 2;
    }

    return result;
  }
};

#endif // DH_HPP
