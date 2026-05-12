#ifndef USER_HPP
#define USER_HPP

#include <random>
#include <stdexcept>

#include "dh.hpp"

template <typename T>
class User {
private:
  DHSetup<T> &setup;
  unsigned long secret;
  bool key_set;
  T symmetric_key;

public:
  User(DHSetup<T> &setup_ref) : setup(setup_ref), key_set(false) {
    std::mt19937_64 gen(std::random_device{}());
    std::uniform_int_distribution<unsigned long> dist(1, T::MOD - 2);
    secret = dist(gen);
  }

  T getPublicKey() const {
    return setup.power(setup.getGenerator(), secret);
  }

  void setKey(T a) {
    symmetric_key = setup.power(a, secret);
    key_set = true;
  }

  T encrypt(T m) const {
    if (!key_set) throw std::logic_error("Encryption without a set key");
    return m * symmetric_key;
  }

  T decrypt(T c) const {
    if (!key_set) throw std::logic_error("Decryption without a set key");
    return c / symmetric_key;
  }
};

#endif // USER_HPP
