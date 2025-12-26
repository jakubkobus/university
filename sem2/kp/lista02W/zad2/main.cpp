#include <stdio.h>
#include <string>
#include <stdexcept>

#include "ArabRzym.hpp"
#include "ArabRzymException.hpp"

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("Brak argumentow\n");
    return 1;
  }

  for(int i = 1; i < argc; i++) {
    try {
      int arab = std::stoi(argv[i]);
      printf("%d - %s\n", arab, ArabRzym::arab2rzym(arab).c_str());
    } catch (const std::invalid_argument &e) {
      std::string rzym = argv[i];
      try {
        printf("%s - %d\n", rzym.c_str(), ArabRzym::rzym2arab(rzym));
      } catch(const ArabRzymException &ex) {
        printf("%s - %s\n", rzym.c_str(), ex.what());
      }
    } catch(const ArabRzymException &e) {
      printf("%s - %s\n", argv[i], e.what());
    }
  }

  return 0;
}