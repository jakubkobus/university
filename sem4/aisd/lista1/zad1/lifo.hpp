#ifndef LIFO_HPP
#define LIFO_HPP

#include <stdio.h>

class LIFO {
private:
  int *data;
  int capacity;
  int top;
  bool debug;

public:
  LIFO(int capacity, bool debug = false)
      : capacity(capacity), top(-1), debug(debug) {
    data = new int[capacity];
  }

  ~LIFO() { delete[] data; }

  void push(int value) {
    if (top == capacity - 1) {
      fprintf(stderr, "[ERROR] Stack is full, data not added\n");
      return;
    }

    data[++top] = value;

    if (debug)
      printf("[DEBUG] Pushed: %d\n", value);
  }

  int pop() {
    if (top == -1) {
      fprintf(stderr, "[ERROR] Stack is empty, data not removed\n");
      return -1;
    }

    int value = data[top--];
    if (debug)
      printf("[DEBUG] Popped: %d\n", value);
    return value;
  }

  bool isEmpty() { return top == -1; }
};

#endif // LIFO_HPP
