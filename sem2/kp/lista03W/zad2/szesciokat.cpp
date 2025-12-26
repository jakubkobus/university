#include "szesciokat.hpp"

Szesciokat::Szesciokat(double b) {
  if(b <= 0)
    throw std::invalid_argument("Bok musi być dodatni.");
  
  bok = b;
}

double Szesciokat::getPole() const {
  return (3 * sqrt(3) * bok * bok) / 2;
}

double Szesciokat::getObwod() const {
  return 6 * bok;
}

std::string Szesciokat::getNazwa() const {
  return "Szesciokat foremny";
}