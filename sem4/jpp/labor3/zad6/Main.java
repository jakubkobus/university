public class Main {

  public static void main(String[] args) {
    final long P = 1234567891L;

    try {
      DHSetup dhSetup = new DHSetup(P);
      System.out.printf(
        "getGenerator() -> %d\n\n",
        dhSetup.getGenerator().get()
      );

      User alice = new User(dhSetup);
      User bob = new User(dhSetup);

      System.out.printf("Alice public key: %d\n", alice.getPublicKey().get());
      System.out.printf("Bob public key: %d\n\n", bob.getPublicKey().get());

      alice.setKey(bob.getPublicKey());
      bob.setKey(alice.getPublicKey());

      Ring message = new Ring(12042026, P);
      System.out.printf("Alice message: %d\n", message.get());

      Ring encrypted = alice.encrypt(message);
      System.out.printf("Encrypted message by Alice: %d\n", encrypted.get());

      Ring decrypted = bob.decrypt(encrypted);
      System.out.printf("Decrypted message by Bob: %d\n", decrypted.get());

      if (message.equals(decrypted)) {
        System.out.printf("[INFO] Success: message == decrypted\n");
      } else {
        System.out.printf("[INFO] Failure: message != decrypted\n");
      }

      User charlie = new User(dhSetup);
      charlie.decrypt(encrypted);
    } catch (Exception ex) {
      System.err.printf("[WARN] Exception catched: %s\n", ex.getMessage());
    }
  }
}
