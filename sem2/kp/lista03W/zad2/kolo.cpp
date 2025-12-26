#include "kolo.hpp"

Kolo::Kolo(double r) {
  if(r <= 0)
    throw std::invalid_argument("Promien musi byc dodatni");

  promien = r;
}

double Kolo::getPole() const { 
  return M_PI * promien * promien;
}
double Kolo::getObwod() const {
  return 2 * M_PI * promien;
}
std::string Kolo::getNazwa() const {
  return "Kolo";
}