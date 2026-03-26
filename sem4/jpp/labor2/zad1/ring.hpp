#ifndef RING_HPP
#define RING_HPP

#include <stdexcept>

typedef long long ll_t;

template <ll_t N>
class Ring {
private:
  ll_t value;

  ll_t normalize(ll_t v) const {
    ll_t result = v % N;

    if(result < 0)
      result += N;

    return result;
  }

  ll_t extended_gcd(ll_t a, ll_t b, ll_t &x, ll_t &y) const {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }

    ll_t x1, y1;
    ll_t d = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return d;
  }

  ll_t modInverse(ll_t a, ll_t m) const {
    ll_t x, y;
    ll_t g = extended_gcd(a, m, x, y);
    if (g != 1) {
      throw std::domain_error(
          "Non-existent inverse element error: " + std::to_string(a) + "^(-1)"
      );
    }

    return (x % m + m) % m;
  }

public:
  Ring() : value(0) {}
  Ring(ll_t v) : value(normalize(v)) {}
  ~Ring() = default;

  explicit operator ll_t() const { return value; }
  ll_t get() const { return value; }

  Ring &operator=(ll_t v) {
    value = normalize(v);
    return *this;
  }

  Ring &operator+=(const Ring &rhs) {
    value = normalize(value + rhs.value);
    return *this;
  }

  Ring &operator-=(const Ring &rhs) {
    value = normalize(value - rhs.value);
    return *this;
  }

  Ring &operator*=(const Ring &rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Ring &operator/=(const Ring &rhs) {
    if (rhs.value == 0)
      throw std::invalid_argument("Zero division error");

    value = normalize(value * modInverse(rhs.value, N));
    return *this;
  }

  friend Ring operator+(Ring lhs, const Ring &rhs) {
    lhs += rhs;
    return lhs;
  }

  friend Ring operator-(Ring lhs, const Ring &rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend Ring operator*(Ring lhs, const Ring &rhs) {
    lhs *= rhs;
    return lhs;
  }

  friend Ring operator/(Ring lhs, const Ring &rhs) {
    lhs /= rhs;
    return lhs;
  }

  friend bool operator==(const Ring &lhs, const Ring &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const Ring &lhs, const Ring &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator<(const Ring &lhs, const Ring &rhs) {
    return lhs.value < rhs.value;
  }

  friend bool operator>(const Ring &lhs, const Ring &rhs) {
    return lhs.value > rhs.value;
  }

  friend bool operator<=(const Ring &lhs, const Ring &rhs) {
    return lhs.value <= rhs.value;
  }

  friend bool operator>=(const Ring &lhs, const Ring &rhs) {
    return lhs.value >= rhs.value;
  }
};

#endif // RING_HPP
