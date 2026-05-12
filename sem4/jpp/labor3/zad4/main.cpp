#include <stdio.h>
#include <iostream>

#include "ring.hpp"
#include "dh.hpp"
#include "user.hpp"

int main() {
  const ll_t P = 1234567891;
  using DHRing = Ring<P>;

  try {
    DHSetup<DHRing> dhSetup;
    printf("getGenerator() -> %lld\n\n", dhSetup.getGenerator().get());
    // std::cout << "getGenerator() -> " << dhSetup.getGenerator() << "\n\n";

    User<DHRing> alice(dhSetup);
    User<DHRing> bob(dhSetup);

    printf("Alice public key: %lld\n", alice.getPublicKey().get());
    // std::cout << "Alice public key: " << alice_public << "\n";
    printf("Bob public key: %lld\n\n", bob.getPublicKey().get());
    // std::cout << "Bob public key: " << bob_public << "\n\n";

    alice.setKey(bob.getPublicKey());
    bob.setKey(alice.getPublicKey());

    DHRing message(12042026);
    printf("Alice message: %lld\n", message.get());
    // std::cout << "Alice message: " << message << "\n";

    DHRing encrypted = alice.encrypt(message);
    printf("Encrypted message by Alice: %lld\n", encrypted.get());
    // std::cout << "Encrypted Alice message: " << encrypted << "\n";

    DHRing decrypted = bob.decrypt(encrypted);
    printf("Decrypted message by Bob: %lld\n", decrypted.get());
    // std::cout << "Decrypted message by Bob: " << decrypted << "\n";

    if (message == decrypted) {
      printf("[INFO] Success: message == decrypted\n");
      // std::cout << "[INFO] Success: message == decrypted\n";
    } else {
      printf("[INFO] Failure: message != decrypted\n");
      // std::cout << "[INFO] Failure: message != decrypted\n";
    }

    User<DHRing> charlie(dhSetup);
    charlie.decrypt(encrypted);
  } catch (const std::exception &ex) {
    fprintf(stderr, "[WARN] Exception catched: %s\n", ex.what());
  }

  return 0;
}
