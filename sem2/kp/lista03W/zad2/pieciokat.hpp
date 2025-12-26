#ifndef PIECIOKAT_HPP
#define PIECIOKAT_HPP

#include "figura.hpp"

class Pieciokat : public Figura {
  double bok;
public:
  Pieciokat(double b);
  double getPole() const override;
  double getObwod() const override;
  std::string getNazwa() const override;
};

#endif // PIECIOKAT_HPP