#include "kwadrat.hpp"

Kwadrat::Kwadrat(double bok) : Czworokat(bok, bok, bok, bok, 90) {
  if(bok <= 0)
    throw std::invalid_argument("Bok musi byc dodatni");
}

double Kwadrat::getPole() const {
  return bok1 * bok1;
}

double Kwadrat::getObwod() const {
  return 4 * bok1;
}

std::string Kwadrat::getNazwa() const {
  return "Kwadrat";
}