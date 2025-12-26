#include <stdio.h>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <cctype>
#include <algorithm>

#include "figura.hpp"
#include "kolo.hpp"
#include "kwadrat.hpp"
#include "romb.hpp"
#include "prostokat.hpp"
#include "pieciokat.hpp"
#include "szesciokat.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  vector<unique_ptr<Figura>> figury;
  
  try {
    int i = 1;
    while(i < argc) {
      char typ = tolower(argv[i++][0]);
      
      if(typ == 'o') {
        if(i >= argc)
          throw invalid_argument("Brak promienia dla kola");

        double r = stod(argv[i++]);
        figury.push_back(make_unique<Kolo>(r));
      } else if (typ == 'p' || typ == 's') {
        if(i >= argc)
          throw invalid_argument("Brak boku");

        double a = stod(argv[i++]);
        if(typ == 'p')
          figury.push_back(make_unique<Pieciokat>(a));
        else
          figury.push_back(make_unique<Szesciokat>(a));
      } else if (typ == 'c') {
        vector<double> params;

        while(i < argc && (isdigit(argv[i][0]) || argv[i][0] == '.'))
          params.push_back(stod(argv[i++]));

        if(params.size() == 2) {
          double bok = params[0],
                 kat = params[1];
          
          if(kat == 90)
            figury.push_back(make_unique<Kwadrat>(bok));
          else
            figury.push_back(make_unique<Romb>(bok, kat));
            
        } else if(params.size() == 5) {
          vector<double> boki{params[0], params[1], params[2], params[3]};
          sort(boki.begin(), boki.end());
          
          if(boki[0] == boki[3]) {
            if(params[4] == 90)
              figury.push_back(make_unique<Kwadrat>(boki[0]));
            else
              figury.push_back(make_unique<Romb>(boki[0], params[4]));
          } else if (boki[0] == boki[1] && boki[2] == boki[3] && params[4] == 90) {
              figury.push_back(make_unique<Prostokat>(boki[0], boki[2]));
          } else throw invalid_argument("Nieprawidlowe parametry dla czworokata");
        } else throw invalid_argument("Nieprawidlowa liczba parametrow dla czworokata");
      } else {
        throw invalid_argument("Nieznany typ figury: " + string(1, typ));
      }
    }
  } catch (const exception& e) {
    printf("Blad: %s\n", e.what());
    return 1;
  }

  for(auto &f : figury)
    printf("%s: Obwod = %.2f | Pole = %.2f\n",
      f->getNazwa().c_str(),
      f->getObwod(),
      f->getPole()
    );

  return 0;
}