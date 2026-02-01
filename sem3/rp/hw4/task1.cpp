#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

#define FILENAME "results/task1.csv"

double binomialPMF(int n, int k);

int main() {
  const int nValues[] = { 100, 1000, 10000 };
  std::ofstream file(FILENAME);

  file << std::scientific << std::setprecision(5);
  file << "n;E(X);MarkovA;ChebyshevA;exactA;MarkovB;ChebyshevB;exactB\n";

  double EX, VarX, MAD, aExact, bExact, a, b, prob, aMarkov,
         aDifference, aChebyshev, bMarkov, bChebyshev;

  for(auto n : nValues) {
    EX = n / 2.0;
    VarX = n / 4.0;

    MAD = 0.0;
    aExact = 0.0;
    bExact = 0.0;

    a = 1.2 * EX;
    b = 0.1 * EX;

    for(int k = 0; k <= n; ++k) {
      prob = binomialPMF(n, k);

      MAD += abs(k - EX) * prob;

      if(k >= ceil(a))
        aExact += prob;

      if(abs(k - EX) >= b)
        bExact += prob;
    }

    aMarkov = EX / a;
    aDifference = a - EX;
    aChebyshev = 0.5 * (VarX / (aDifference * aDifference));

    if(aChebyshev > 1.0)
      aChebyshev = 1.0;

    bMarkov = MAD / b;

    bChebyshev = VarX / (b * b);
    if (bChebyshev > 1.0)
      bChebyshev = 1.0;

    file << n << ";" << EX << ";" << aMarkov << ";" << aChebyshev << ";"
         << aExact << ";" << bMarkov << ";" << bChebyshev << ";" << bExact
         << "\n";
  }

  file.close();
  return 0;
}

double binomialPMF(int n, int k) {
  double p = 1.0;
  int halvesUsed = 0;

  for(int i = 1; i <= k; i++) {
    p *= (double)(n - i + 1) / i;

    while(p > 1.0e10 && halvesUsed < n) {
      p *= 0.5;
      halvesUsed++;
    }
  }

  while(halvesUsed < n) {
    p *= 0.5;
    halvesUsed++;
  }

  return p;
}