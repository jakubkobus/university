#include "romb.hpp"

Romb::Romb(double bok, double k) : Czworokat(bok, bok, bok, bok, k) {
  if(bok <= 0)
    throw std::invalid_argument("Bok musi byc dodatni");
  if(k <= 0 || k >= 180)
    throw std::invalid_argument("Kat musi byc wiekszy od 0 i mniejszy od 180");
}

double Romb::getPole() const {
  return bok1 * bok1 * sin(kat * M_PI / 180.0);
}

double Romb::getObwod() const {
  return 4 * bok1;
}

std::string Romb::getNazwa() const {
  return "Romb";
}