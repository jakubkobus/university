#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lib.h"

int stringToInt(char *str) {
  int result = 0;
  for(int i = 0; str[i] != '\0'; i++) {
    if(!isdigit(str[i]))
      return -1;
    
    result = result * 10 + str[i] - '0';
  }
  return result;
}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("Nieprawidlowe uzycie\n");
    return 1;
  }

  int number = stringToInt(argv[2]);
  if(number == -1) {
    printf("Nieprawidlowa liczba\n");
    return 1;
  }

  if(strcmp(argv[1], "pn") == 0) {
    printf("%d\n", countPrimes(number));
  } else if(strcmp(argv[1], "pr") == 0) {
    printf("%d\n", nthPrime(number));
  } else if(strcmp(argv[1], "ip") == 0) {
    printf("%s\n", isPrime(number) ? "true" : "false");
  } else {
    printf("Nieprawidlowe uzycie\n");
    return 1;
  }

  return 0;
}