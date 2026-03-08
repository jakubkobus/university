#ifndef FIFO_HPP
#define FIFO_HPP

#include <stdio.h>

class FIFO {
private:
  int *data;
  int capacity;
  int front;
  int back;
  bool debug;

public:
  FIFO(int capacity, bool debug = false)
      : capacity(capacity), front(0), back(0), debug(debug) {
    data = new int[capacity];
  }

  ~FIFO() { delete[] data; }

  void push(int value) {
    if (back - front >= capacity) {
      fprintf(stderr, "[ERROR] Queue is full, element not added\n");
      return;
    }

    data[back % capacity] = value;
    back = (back == 2 * capacity - 1) ? 0 : back + 1;

    if (debug)
      printf("[DEBUG] Pushed: %d\n", value);
  }

  int pop() {
    if (front == back) {
      fprintf(stderr, "[ERROR] Queue is empty, data not removed\n");
      return -1;
    }

    int value = data[front % capacity];
    front = (front == 2 * capacity - 1) ? 0 : front + 1;

    if (debug)
      printf("[DEBUG] Popped: %d\n", value);

    return value;
  }

  bool isEmpty() { return front == back; }
};

#endif // FIFO_HPP
