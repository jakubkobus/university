#include "pieciokat.hpp"

Pieciokat::Pieciokat(double b) {
  if(b <= 0)
    throw std::invalid_argument("Bok pieciokata musi byc dodatni.");

  bok = b;
}

double Pieciokat::getPole() const {
  return (5 * bok * bok) / (4 * tan(M_PI / 5));
}

double Pieciokat::getObwod() const {
  return 5 * bok;
}

std::string Pieciokat::getNazwa() const {
  return "Pieciokat foremny";
}