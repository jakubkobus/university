#include "types.h"
#include "stat.h"
#include "user.h"

/*
 [0] Biały (default)
 [1] Czerwony
 [2] Zielony
 [3] Niebieski
 [4] Żółty
 [5] Magenta
 [6] Cyjan
 [7] Biały
 [8] Szary
 */

int main(int argc, char *argv[]) {
  printf(1, "%1Hello, World!\n");
  printf(1, "%2Hello, World!\n");
  printf(1, "%3Hello, World!\n");
  printf(1, "%4Hello, World!\n");
  printf(1, "%5Hello, World!\n");
  printf(1, "%6Hello, World!\n");
  printf(1, "%7Hello, World!\n");
  printf(1, "%8Hello, World!%0\n");

  exit();
}