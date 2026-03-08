#ifndef DOUBLE_NODE_HPP
#define DOUBLE_NODE_HPP

struct DoubleNode {
  int value;
  DoubleNode *next;
  DoubleNode *prev;

  DoubleNode(int val) : value(val), next(nullptr), prev(nullptr) {}
  ~DoubleNode() = default;
};

#endif // DOUBLE_NODE_HPP
