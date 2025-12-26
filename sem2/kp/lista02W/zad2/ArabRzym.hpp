#ifndef ARABRZYM_HPP
#define ARABRZYM_HPP

#include <string>

#include "ArabRzymException.hpp"

class ArabRzym {
  static const std::string liczbyRzymskie[];
  static const int liczbyArabskie[];

  public:
    static int rzym2arab(const std::string& rzym);
    static std::string arab2rzym(int arab);
};

#endif // ARABRZYM_HPP