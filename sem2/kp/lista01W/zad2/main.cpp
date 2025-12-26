#include <stdio.h>
#include <cstdlib>
#include <stdexcept>

#include "WierszTrojkataPascala.hpp"

int main(int argc, char *argv[]) {
    if(argc < 2) {
      printf("Brak argumentow\n");
      return 1;
    }

    int n;
    WierszTrojkataPascala *wiersz;

    try {
      n = std::stoi(argv[1]);

      if(n < 0)
        throw std::invalid_argument("");

      wiersz = new WierszTrojkataPascala(n);
      wiersz->wygenerujWiersz();
    } catch (const std::invalid_argument& e) {
      printf("%s - Nieprawidlowy numer wiersza\n", argv[1]);
      return 1;
    }

    for(int i = 2; i < argc; ++i) {
      try {
        int m = std::stoi(argv[i]);

        if(m < 0 || m > n)
          throw std::out_of_range("");

        printf("%s - %d\n", argv[i], wiersz->m_tyElementWiersza(m));
      } catch(const std::invalid_argument &e) {
        printf("%s - nieprawidlowa dana\n", argv[i]);
      } catch(const std::out_of_range &e) {
        printf("%s - liczba spoza zakresu\n", argv[i]);
      }
    }

    delete wiersz;
    return 0;
}