#include "WierszTrojkataPascala.hpp"

WierszTrojkataPascala::WierszTrojkataPascala(int n) {
  this->n = n;
}

WierszTrojkataPascala::~WierszTrojkataPascala() {
  if(wiersz != nullptr) delete wiersz;
}

void WierszTrojkataPascala::wygenerujWiersz() {
  wiersz = (int *)malloc((n + 1) * sizeof(int));
  wiersz[0] = 1;

  for(int i = 1; i <= n; i++)
    wiersz[i] = wiersz[i - 1] * (n - i + 1) / i;
}

int WierszTrojkataPascala::m_tyElementWiersza(int m) {
  return wiersz[m];
}
