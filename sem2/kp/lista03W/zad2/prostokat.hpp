#ifndef PROSTOKAT_HPP
#define PROSTOKAT_HPP

#include "czworokat.hpp"

class Prostokat : public Czworokat {
  public:
    Prostokat(double b1, double b2);
    double getPole() const override;
    double getObwod() const override;
    std::string getNazwa() const override;
  };

#endif // PROSTOKAT_HPP