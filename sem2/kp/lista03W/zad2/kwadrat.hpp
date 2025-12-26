#ifndef KWADRAT_HPP
#define KWADRAT_HPP

#include "czworokat.hpp"

class Kwadrat : public Czworokat {
  public:
    Kwadrat(double bok);
    double getPole() const override;
    double getObwod() const override;
    std::string getNazwa() const override;
  };

#endif // KWADRAT_HPP