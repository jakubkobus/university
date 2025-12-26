#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <bits/types/sigset_t.h>
#include <bits/sigaction.h>

volatile sig_atomic_t count = 0;

void handler(int signal) {
  count++;
}

int main() {    
  signal(SIGUSR1, handler);

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  
  sigprocmask(SIG_BLOCK, &set, NULL);
  
  printf("SIGUSR1 zablokowany na 10 sekund\n");
  printf("> kill -SIGUSR1 %d\n", getpid());
  sleep(10);
  
  sigprocmask(SIG_UNBLOCK, &set, NULL);

  printf("\nOdblokowany\n");
  
  printf("Liczba odebranych sygnalow - %d\n", count);

  return 0;
}