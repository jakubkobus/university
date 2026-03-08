#ifndef DOUBLY_CYCLED_LINKED_LIST_HPP
#define DOUBLY_CYCLED_LINKED_LIST_HPP

#include <stdio.h>

#include "double_node.hpp"

class DoublyCycledLinkedList {
public:
  DoubleNode *head;
  size_t size;

  DoublyCycledLinkedList() : head(nullptr), size(0) {}

  ~DoublyCycledLinkedList() {
    if (!head)
      return;

    DoubleNode *temp = head->next;
    while (temp != head) {
      DoubleNode *nextNode = temp->next;
      delete temp;
      temp = nextNode;
    }

    delete head;
  }

  void print() const {
    if (!head) {
      printf("[WARN] List is empty\n");
      return;
    }

    DoubleNode *temp = head->next;
    printf("size=%lu [ ", size);
    do {
      printf("%d ", temp->value);
      temp = temp->next;
    } while (temp != head->next);
    printf("]\n");
  }
};

#endif // DOUBLY_CYCLED_LINKED_LIST_HPP
