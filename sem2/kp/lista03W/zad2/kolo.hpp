#ifndef KOLO_HPP
#define KOLO_HPP

#include "figura.hpp"

class Kolo : public Figura {
  double promien;
public:
  Kolo(double r);
  double getPole() const override;
  double getObwod() const override;
  std::string getNazwa() const override;
};

#endif // KOLO_HPP