#ifndef SZESCIOKAT_HPP
#define SZESCIOKAT_HPP

#include "figura.hpp"

class Szesciokat : public Figura {
  double bok;
public:
  Szesciokat(double b);
  double getPole() const override;
  double getObwod() const override;
  std::string getNazwa() const override;
};

#endif // SZESCIOKAT_HPP