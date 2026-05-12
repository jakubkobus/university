#include <cstdio>
#include <iostream>

#include "ring.hpp"
#include "rsa.hpp"

int main() {
  const ll_t p = 10007;
  const ll_t q = 10009;
  using RSA_Ring = Ring<p * q>;

  try {
    RSA<RSA_Ring> rsa(p, q);

    printf("Public key: %lld\n", rsa.getPublicKey().get());
    // std::cout << "Public key: " << rsa.getPublicKey() << '\n';
    printf("getModulo() -> %u\n\n", rsa.getModulo());
    // std::cout << "getModulo() -> " << rsa.getModulo() << "\n\n";

    RSA_Ring message(12042026);
    printf("Message: %lld\n", message.get());
    // std::cout << "Message: " << message << '\n';

    RSA_Ring encrypted = rsa.encrypt(message);
    printf("Encrypted: %lld\n", encrypted.get());
    // std::cout << "Encrypted: " << encrypted << '\n';

    RSA_Ring decrypted = rsa.decrypt(encrypted);
    printf("Decrypted: %lld\n", decrypted.get());
    // std::cout << "Decrypted: " << decrypted << '\n';

    if (message == decrypted) {
      printf("[INFO] Success: message == decrypted\n");
      // std::cout << "[INFO] Success: message == decrypted\n";
    } else {
      printf("[INFO] Failure: message != decrypted\n");
      // std::cout << "[INFO] Failure: message != decrypted\n";
    }
  } catch (const std::exception &ex) {
    fprintf(stderr, "[WARN] Exception catched: %s\n", ex.what());
  }

  return 0;
}
