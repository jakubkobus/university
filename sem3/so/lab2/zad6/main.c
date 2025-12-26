#include <stdio.h>

int main() {
  const char *text = "Hello, World!";

  // 30-37 zwykle | 90-97 jasne
  for(int i = 0; i < 8; i++) {
    printf("\x1b[%dm%s\n\x1b[%dm%s\n", 30 + i, text, 90 + i, text); 
  }

  printf("\x1b[0m");
  return 0;
}
