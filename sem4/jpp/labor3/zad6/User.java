import java.util.Random;

public class User {

  private final DHSetup setup;
  private final long secret;
  private boolean keySet;
  private Ring symmetricKey;

  private final Random gen = new Random();

  public User(DHSetup setup) {
    this.setup = setup;
    this.keySet = false;

    this.secret = gen.nextLong(1, setup.getP() - 1);
  }

  public Ring getPublicKey() {
    return setup.power(setup.getGenerator(), secret);
  }

  public void setKey(Ring otherPublicKey) {
    this.symmetricKey = setup.power(otherPublicKey, secret);
    this.keySet = true;
  }

  public Ring encrypt(Ring m) {
    if (!keySet) {
      throw new IllegalStateException("Encrypting without a set key");
    }
    return m.mul(symmetricKey);
  }

  public Ring decrypt(Ring c) {
    if (!keySet) {
      throw new IllegalStateException("Decrypting without a set key");
    }
    return c.div(symmetricKey);
  }
}
