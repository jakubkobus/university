#ifndef ROMB_HPP
#define ROMB_HPP

#include "czworokat.hpp"

class Romb : public Czworokat {
  public:
    Romb(double bok, double k);
    double getPole() const override;
    double getObwod() const override;
    std::string getNazwa() const override;
  };

#endif // ROMB_HPP