import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DHSetup {

  private final Ring generator;
  private final long p;

  private final Random gen = new Random();

  private List<Long> getPrimeFactors(long n) {
    List<Long> factors = new ArrayList<>();

    for (long i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        factors.add(i);
        while (n % i == 0) n /= i;
      }
    }

    if (n > 1) factors.add(n);

    return factors;
  }

  public DHSetup(long p) {
    this.p = p;
    List<Long> factors = getPrimeFactors(p - 1);

    while (true) {
      long a = gen.nextLong(1, p);
      Ring candidate = new Ring(a, p);
      boolean isGenerator = true;

      for (long q : factors) {
        Ring res = power(candidate, (p - 1) / q);
        if (res.get() == 1) {
          isGenerator = false;
          break;
        }
      }

      if (isGenerator) {
        this.generator = candidate;
        break;
      }
    }
  }

  public Ring getGenerator() {
    return generator;
  }

  public long getP() {
    return p;
  }

  public Ring power(Ring base, long exp) {
    Ring result = new Ring(1, base.getMod());

    while (exp > 0) {
      if (exp % 2 == 1) {
        result = result.mul(base);
      }

      base = base.mul(base);
      exp /= 2;
    }

    return result;
  }
}
