#ifndef BST_NODE_HPP
#define BST_NODE_HPP

#include <limits.h>

struct BST_Node {
  int key;
  BST_Node *parent;
  BST_Node *left;
  BST_Node *right;

  BST_Node() : key(INT_MIN), parent(nullptr), left(nullptr), right(nullptr) {}
  BST_Node(const int key) : key(key), parent(nullptr), left(nullptr), right(nullptr) {}
};

#endif // BST_NODE_HPP
