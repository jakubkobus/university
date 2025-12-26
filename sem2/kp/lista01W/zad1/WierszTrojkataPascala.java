public class WierszTrojkataPascala {
  private int n;
  private int[] wiersz;

  public WierszTrojkataPascala(int n) {
    this.n = n;
  }

  public void wygenerujWiersz() {
    this.wiersz = new int[n + 1];
    this.wiersz[0] = 1;

    for(int i = 1; i <= n; i++)
      this.wiersz[i] = this.wiersz[i - 1] * (n - i + 1) / i;
  }

  public int m_tyElementWiersza(int m) {
    return this.wiersz[m];
  }
}