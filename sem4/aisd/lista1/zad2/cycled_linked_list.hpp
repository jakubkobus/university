#ifndef CYCLED_LINKED_LIST_HPP
#define CYCLED_LINKED_LIST_HPP

#include <stdio.h>

#include "node.hpp"

class CycledLinkedList {
public:
  Node *head;
  size_t size;

  CycledLinkedList() : head(nullptr), size(0) {}

  ~CycledLinkedList() {
    if (!head)
      return;

    Node *temp = head->next;
    while (temp != head) {
      Node *nextNode = temp->next;
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

    Node *temp = head->next;
    printf("size=%lu [ ", size);
    do {
      printf("%d ", temp->value);
      temp = temp->next;
    } while (temp != head->next);
    printf("]\n");
  }
};

#endif // CYCLED_LINKED_LIST_HPP
