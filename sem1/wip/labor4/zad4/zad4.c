#include <stdio.h>
#include <ctype.h>

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
  if(argc < 2) {
    printf("Nieprawidlowe uzycie\n");
    return 1;
  } 

  int number;
  for(int i = 1; i < argc; i++) {
    number = stringToInt(argv[i]);
    
    if(number == -1)
      printf("totient('%s') = ERROR\n", argv[i]);
    else
      printf("totient(%d) = %d\n", number, totient(number));
  }

  return 0;
}