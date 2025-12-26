#include "prostokat.hpp"

Prostokat::Prostokat(double b1, double b2) : Czworokat(b1, b2, b1, b2, 90) {
  if(b1 <= 0 || b2 <= 0)
    throw std::invalid_argument("Boki prostokata musza byc dodatnie.");
}

double Prostokat::getPole() const {
  return bok1 * bok2;
}

double Prostokat::getObwod() const {
  return 2 * (bok1 + bok2);
}

std::string Prostokat::getNazwa() const {
  return "Prostokat";
}