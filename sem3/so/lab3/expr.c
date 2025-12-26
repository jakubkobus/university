#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int num1, num2, result;
  char op;

  if (argc != 4)
  {
    printf(2, "Usage: expr <number> <operator> <number>\n");
    exit();
  }

  num1 = atoi(argv[1]);
  op = argv[2][0];
  num2 = atoi(argv[3]);

  switch (op)
  {
  case '+':
    result = num1 + num2;
    break;
  case '-':
    result = num1 - num2;
    break;
  case '*':
    result = num1 * num2;
    break;
  case '/':
    if (num2 == 0)
    {
      printf(2, "Zero division error\n");
      exit();
    }
    result = num1 / num2;
    break;
  default:
    printf(2, "Unknown operator '%c'\n", op);
    exit();
  }

  printf(1, "%d\n", result);

  exit();
}
