#define WIDTH 80
#define HEIGHT 25

void clear_the_screen(char *video_memory, unsigned char color);
void print_string(char *video_memory, const char *str, int line, unsigned char color);

void main() {
  char *video_memory = (char *) 0xB8000;

  clear_the_screen(video_memory, 0);

  const char *text = "Hello World!                                                                   ";
  int line = 0;
  unsigned char color;

  for(int clr = 0; clr < 16; clr++) {
    color = (clr << 4) | (15 - clr);
    print_string(video_memory, text, line++, color);
  }

  while (1) {}
}

void clear_the_screen(char *video_memory, unsigned char color) {
  for(int i = 0; i < WIDTH * HEIGHT * 2; i += 2) {
    video_memory[i] = ' ';
    video_memory[i + 1] = color;
  }
}

void print_string(char *video_memory, const char *str, int line, unsigned char color) {
  int line_beginning = line * WIDTH * 2;

  for(int i = 0; str[i] != '\0'; i++) {
    video_memory[line_beginning + i * 2] = str[i];
    video_memory[line_beginning + i * 2 + 1] = color;

    if(i > WIDTH - 1)
      break;
  }
}
