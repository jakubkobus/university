public class Ring {

  private final long value;
  private final long MOD;

  private static long normalize(long v, long mod) {
    long result = v % mod;
    if (result < 0) {
      result += mod;
    }
    return result;
  }

  private long[] extendedGCD(long a, long b) {
    if (b == 0) return new long[] { a, 1, 0 };

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
    if (res[0] != 1) throw new ArithmeticException(
      "Non-existent inverse element error: " + a + "^(-1)"
    );

    return ((res[1] % m) + m) % m;
  }

  public Ring(long v, long mod) {
    this.MOD = mod;
    this.value = normalize(v, mod);
  }

  public long get() {
    return value;
  }

  public long getMod() {
    return MOD;
  }

  public Ring add(Ring rhs) {
    return new Ring(this.value + rhs.value, this.MOD);
  }

  public Ring sub(Ring rhs) {
    return new Ring(this.value - rhs.value, this.MOD);
  }

  public Ring mul(Ring rhs) {
    return new Ring(this.value * rhs.value, this.MOD);
  }

  public Ring div(Ring rhs) {
    if (rhs.value == 0) throw new IllegalArgumentException(
      "Zero division error"
    );

    return new Ring(this.value * modInverse(rhs.value, this.MOD), this.MOD);
  }

  public boolean equals(Ring rhs) {
    return this.value == rhs.value && this.MOD == rhs.MOD;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (!(obj instanceof Ring)) return false;
    return equals((Ring) obj);
  }

  @Override
  public String toString() {
    return String.valueOf(value);
  }
}
