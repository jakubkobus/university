#ifndef CZWOROKAT_HPP
#define CZWOROKAT_HPP

#include <string>
#include <stdexcept>
#include <cmath>
#include "figura.hpp"

class Czworokat : public Figura {
  protected:
    double bok1, bok2, bok3, bok4, kat;
  public:
    Czworokat(
      double b1,
      double b2,
      double b3,
      double b4,
      double kat
    );
};

#endif // CZWOROKAT_HPP