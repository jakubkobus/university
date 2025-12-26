#include <stdio.h>
#include <signal.h>
#include <string.h>

void handler(int signal) {}

int main() {
  for(int i = 1; i < 32; i++)
    if(signal(i, handler) == SIG_ERR)
      printf("Nie mozna obsluzyc sygnalu %d - %s\n", i, strsignal(i));

  return 0;
}