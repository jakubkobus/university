import java.util.Random;

public class RSA {

  private final long _p, _q, _n, _phi, _e, _d;
  private final Random generator = new Random();

  private long gcd(long a, long b) {
    while (b != 0) {
      long temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }

  private long[] extendedGCD(long a, long b) {
    if (b == 0) {
      return new long[] { a, 1, 0 };
    }

    long[] res = extendedGCD(b, a % b);
    long d = res[0];
    long x1 = res[1];
    long y1 = res[2];

    long x = y1;
    long y = x1 - y1 * (a / b);

    return new long[] { d, x, y };
  }

  private long modInverse(long a, long m) {
    long[] res = extendedGCD(a, m);
    if (res[0] != 1) {
      throw new ArithmeticException(
        "Non-existent inverse element error: " + a + "^(-1)"
      );
    }
    return ((res[1] % m) + m) % m;
  }

  private Ring pow(Ring base, long exp) {
    Ring result = new Ring(1, _n);

    while (exp > 0) {
      if (exp % 2 == 1) {
        result = result.mul(base);
      }
      base = base.mul(base);
      exp /= 2;
    }

    return result;
  }

  public RSA(long p, long q, long expectedModulo) {
    this._p = p;
    this._q = q;
    this._n = p * q;

    if (this._n != expectedModulo) {
      throw new IllegalArgumentException(
        "Product of p and q does not fit to the ring characteristics"
      );
    }

    this._phi = (p - 1) * (q - 1);

    long e_candidate;
    do {
      e_candidate = generator.nextLong(2, _phi);
    } while (gcd(e_candidate, _phi) != 1);
    this._e = e_candidate;

    this._d = modInverse(this._e, this._phi);
  }

  public long getModulo() {
    return _n;
  }

  public Ring getPublicKey() {
    return new Ring(_e, _n);
  }

  public Ring encrypt(Ring m) {
    return pow(m, _e);
  }

  public Ring decrypt(Ring s) {
    return pow(s, _d);
  }
}
