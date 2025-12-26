#include "ArabRzym.hpp"

#define NUMS_SIZE 13

const std::string ArabRzym::liczbyRzymskie[] = {
  "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"
};

const int ArabRzym::liczbyArabskie[] = {
  1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000
};

int ArabRzym::rzym2arab(const std::string &rzym)
{
  int value, prevValue = 4000, result = 0, i = 0;
  bool found;

  while((size_t)i < rzym.length()) {
    found = false;

    for(int j = NUMS_SIZE - 1; j >= 0 && !found; j--) {
      if(rzym.compare(i, liczbyRzymskie[j].length(), liczbyRzymskie[j]) == 0) {
        value = liczbyArabskie[j];

        if(value > prevValue)
          throw ArabRzymException("nieprawidlowy zapis");
        
        result += value;
        prevValue = value;
        i += liczbyRzymskie[j].length();
        found = true;
      }
    }

    if(!found)
      throw ArabRzymException("nieprawidlowy zapis");
  }
  
  if(result < 1 || result > 3999)
    throw ArabRzymException("liczba spoza zakresu (1-3999)");

  return result;
}

std::string ArabRzym::arab2rzym(int arab)
{
  if(arab < 1 || arab > 3999)
    throw ArabRzymException("liczba spoza zakresu (1-3999)");
  

  std::string result;
  for(int i = NUMS_SIZE - 1; i >= 0; i--)
    while(arab >= liczbyArabskie[i]) {
      result += liczbyRzymskie[i];
      arab -= liczbyArabskie[i];
    }

  return result;
}
