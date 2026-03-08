#ifndef NODE_HPP
#define NODE_HPP

struct Node {
  int value;
  Node *next;

  Node(int val) : value(val), next(nullptr) {}
  ~Node() = default;
};

#endif // NODE_HPP
