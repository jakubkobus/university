#ifndef WIERSZTROJKATAPASCALA_HPP
#define WIERSZTROJKATAPASCALA_HPP

#include <cstdlib>

class WierszTrojkataPascala {
  int n;
  int *wiersz;

  public:
    WierszTrojkataPascala(int n);
    ~WierszTrojkataPascala();
    void wygenerujWiersz();
    int m_tyElementWiersza(int m);
};

#endif // WIERSZTROJKATAPASCALA_HPP
