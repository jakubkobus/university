#include <random>
#include <stdio.h>
#include <vector>

#include "doubly_cycled_linked_list.hpp"

void insert(DoublyCycledLinkedList &l, int i);
void merge(DoublyCycledLinkedList &l1, DoublyCycledLinkedList &l2);
int searchCost(DoublyCycledLinkedList &l, int target, bool forward);

int main() {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist_dir(0, 1);

  std::uniform_int_distribution<int> dist1(10, 99);
  DoublyCycledLinkedList list1;
  DoublyCycledLinkedList list2;

  for (int i = 0; i < 10; i++) {
    insert(list1, dist1(rng));
    insert(list2, dist1(rng));
  }

  printf("[INFO] Before merge\n");
  list1.print();
  list2.print();

  merge(list1, list2);

  printf("[INFO] After merge\n");
  list1.print();
  list2.print();

  const size_t SIZE = 10000;
  std::uniform_int_distribution<int> dist2(0, 100000);
  std::vector<int> T(SIZE);
  DoublyCycledLinkedList list3;

  for (size_t i = 0; i < SIZE; i++) {
    T[i] = dist2(rng);
    insert(list3, T[i]);
  }

  const size_t TEST_TRIES = 1000;
  std::uniform_int_distribution<int> dist3(0, SIZE - 1);
  unsigned long long totalCostFromArray = 0;

  for (size_t i = 0; i < TEST_TRIES; i++) {
    int target = T[dist3(rng)];
    bool forward = dist_dir(rng) == 1;
    totalCostFromArray += searchCost(list3, target, forward);
  }

  double avgCostFromArray =
      static_cast<double>(totalCostFromArray) / TEST_TRIES;

  long long totalCostAll = 0;

  for (size_t i = 0; i < TEST_TRIES; i++) {
    int target = dist2(rng);
    bool forward = dist_dir(rng) == 1;
    totalCostAll += searchCost(list3, target, forward);
  }
  double avgCostAll = static_cast<double>(totalCostAll) / TEST_TRIES;

  printf("[INFO] Average cost of searching for elements from the array: "
         "%.2f comparisons\n",
         avgCostFromArray);
  printf("[INFO] Average cost of searching for random elements from the range: "
         "%.2f comparisons\n",
         avgCostAll);

  return 0;
}

void insert(DoublyCycledLinkedList &l, int i) {
  DoubleNode *newNode = new DoubleNode(i);

  if (!l.head) {
    l.head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
  } else {
    DoubleNode *first = l.head->next;

    newNode->next = first;
    newNode->prev = l.head;

    first->prev = newNode;
    l.head->next = newNode;

    l.head = newNode;
  }

  l.size++;
}

void merge(DoublyCycledLinkedList &l1, DoublyCycledLinkedList &l2) {
  if (!l2.head)
    return;

  if (!l1.head) {
    l1.head = l2.head;
    l1.size = l2.size;
    l2.head = nullptr;
    l2.size = 0;
    return;
  }

  DoubleNode *firstOfL1 = l1.head->next;
  DoubleNode *firstOfL2 = l2.head->next;

  l1.head->next = firstOfL2;
  firstOfL2->prev = l1.head;

  l2.head->next = firstOfL1;
  firstOfL1->prev = l2.head;

  l1.head = l2.head;
  l1.size += l2.size;

  l2.head = nullptr;
  l2.size = 0;
}

int searchCost(DoublyCycledLinkedList &l, int target, bool forward) {
  if (!l.head)
    return 0;

  int comparisons = 0;

  if (forward) {
    DoubleNode *temp = l.head->next;
    do {
      comparisons++;
      if (temp->value == target)
        return comparisons;
      temp = temp->next;
    } while (temp != l.head->next);
  } else {
    DoubleNode *temp = l.head;
    do {
      comparisons++;
      if (temp->value == target)
        return comparisons;
      temp = temp->prev;
    } while (temp != l.head);
  }

  return comparisons;
}
