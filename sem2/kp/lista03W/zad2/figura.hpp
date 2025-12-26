#ifndef FIGURA_HPP
#define FIGURA_HPP

#include <string>
#include <cmath>
#include <stdexcept>

class Figura {
  public:
    virtual double getPole() const = 0;
    virtual double getObwod() const = 0;
    virtual std::string getNazwa() const = 0;
    virtual ~Figura(){}
};

#endif // FIGURA_HPP