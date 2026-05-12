#ifndef RSA_HPP
#define RSA_HPP

#include <stdexcept>
#include <random>

#include "ring.hpp"

template <typename T>
class RSA {
private:
  ll_t _p, _q, _n, _phi, _e, _d;

  ll_t gcd(ll_t a, ll_t b) const {
    while (b != 0) {
      ll_t temp = b;
      b = a % b;
      a = temp;
    }

    return a;
  }

  ll_t extendedGCD(ll_t a, ll_t b, ll_t &x, ll_t &y) const {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }

    ll_t x1, y1;
    ll_t d = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return d;
  }

  ll_t modInverse(ll_t a, ll_t m) const {
    ll_t x, y;
    ll_t g = extendedGCD(a, m, x, y);
    if (g != 1) {
      throw std::domain_error(
          "Non-existent inverse element error: " + std::to_string(a) + "^(-1)"
      );
    }

    return (x % m + m) % m;
  }

  T pow(T base, ll_t exp) const {
    T result(1);

    while (exp > 0) {
      if (exp % 2 == 1)
        result *= base;

      base *= base;
      exp /= 2;
    }

    return result;
  }

public:
  RSA(ll_t p, ll_t q) : _p(p), _q(q) {
    _n = p * q;

    if (_n != T::MOD)
      throw std::invalid_argument(
        "Product of p and q does not fit to the ring characteristics"
      );


    _phi = (p - 1) * (q - 1);

    std::mt19937_64 gen(std::random_device{}());
    std::uniform_int_distribution<ll_t> dist(2, _phi - 1);

    do {
      _e = dist(gen);
    } while (gcd(_e, _phi) != 1);

    _d = modInverse(_e, _phi);
  }

  ~RSA() = default;

  unsigned getModulo() const {
    return static_cast<unsigned>(_n);
  }

  T getPublicKey() const {
    return T(_e);
  }

  T encrypt(T m) const {
    return pow(m, _e);
  }

  T decrypt(T s) const {
    return pow(s, _d);
  }
};

#endif // RSA_HPP
