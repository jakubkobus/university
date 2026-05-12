public class Main {

  public static void main(String[] args) {
    final long p = 10007;
    final long q = 10009;
    final long n = p * q;

    try {
      RSA rsa = new RSA(p, q, n);

      System.out.printf("Public key: %d\n", rsa.getPublicKey().get());
      System.out.printf("getModulo() -> %d\n\n", rsa.getModulo());

      Ring message = new Ring(12042026, n);
      System.out.printf("Message: %d\n", message.get());

      Ring encrypted = rsa.encrypt(message);
      System.out.printf("Encrypted: %d\n", encrypted.get());

      Ring decrypted = rsa.decrypt(encrypted);
      System.out.printf("Decrypted: %d\n", decrypted.get());

      if (message.equals(decrypted)) System.out.println(
        "[INFO] Success: message == decrypted"
      );
      else System.out.println("[INFO] Failure: message != decrypted");
    } catch (Exception ex) {
      System.err.printf("[WARN] Exception catched: %s\n", ex.getMessage());
    }
  }
}
