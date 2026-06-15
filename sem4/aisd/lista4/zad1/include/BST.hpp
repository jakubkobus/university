#ifndef BST_HPP
#define BST_HPP

#include <stdio.h>
#include <string>

#include "BST_Node.hpp"
#include "Stats.hpp"

class BST {
private:
  BST_Node *_root;

  BST_Node *_tree_minimum(BST_Node *x, Stats &s) const {
    s.ptr += 1;
    while(x->left != nullptr) {
      x = x->left;
      s.ptr += 2;
    }

    return x;
  }

  BST_Node *_tree_successor(BST_Node *x, Stats &s) const {
    s.ptr += 1;
    if(x->right != nullptr) {
      s.ptr += 1;
      return _tree_minimum(x->right, s);
    }

    BST_Node *y = x->parent;
    s.ptr += 1;

    s.ptr += 1;
    while(y != nullptr && x == y->right) {
      x = y;
      y = y->parent;
      s.ptr += 2;
    }

    return y;
  }

  BST_Node *_recursive_search(BST_Node *x, const int key, Stats &s) const {
    if(x == nullptr)
      return x;

    s.cmp += 1;
    if(x->key == key)
      return x;

    s.cmp += 1;
    if(key < x->key) {
      s.ptr += 1;
      return _recursive_search(x->left, key, s);
    } else {
      s.ptr +=1;
      return _recursive_search(x->right, key, s);
    }
  }

  BST_Node *_delete_node(BST_Node *node, Stats &s) {
    BST_Node *y = nullptr;

    s.ptr += 2;
    if(node->left == nullptr || node->right == nullptr)
      y = node;
    else
      y = _tree_successor(node, s);

    BST_Node *x = nullptr;
    s.ptr += 1;
    if(y->left != nullptr) {
      x = y->left;
      s.ptr += 1;
    } else {
      x = y->right;
      s.ptr += 1;
    }

    if(x != nullptr) {
      x->parent = y->parent;
      s.ptr += 2;
    }

    s.ptr += 1;
    if(y->parent == nullptr) {
      _root = x;
      s.ptr += 1;
    } else {
      s.ptr += 1;
      if(y == y->parent->left) {
        y->parent->left = x;
        s.ptr += 1;
      } else {
        y->parent->right = x;
        s.ptr += 1;
      }
    }

    if(y != node)
      node->key = y->key;

    return y;
  }

  int _height(BST_Node *node) const {
    if (node == nullptr)
      return 0;

    int leftHeight = _height(node->left);
    int rightHeight = _height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
  }

  void _printTree(BST_Node* node, std::string prefix, int dir) const {
    if (node == nullptr) return;

    std::string newPrefixR = prefix + (dir == -1 ? "|  " : "   ");
    _printTree(node->right, newPrefixR, 1);

    printf("%s", prefix.c_str());
    if (dir == 0) printf("-");
    else if (dir == 1) printf("/-");
    else printf("\\-");
    printf("[%d]\n", node->key);

    std::string newPrefixL = prefix + (dir == 1 ? "|  " : "   ");
    _printTree(node->left, newPrefixL, -1);
  }

public:
  BST() :
    _root(nullptr) {}

  BST(const int key) :
    _root(new BST_Node(key)) {}

  int height() const {
    return _height(_root);
  }

  void insertNode(const int key, Stats &s) {
    BST_Node *y = nullptr;
    BST_Node *x = _root;
    s.ptr += 1;


    while(x != nullptr) {
      y = x;
      s.cmp += 1;
      if(key < x->key) {
        x = x->left;
        s.ptr += 1;
      } else {
        x = x->right;
        s.ptr += 1;
      }
    }

    BST_Node *z = new BST_Node(key);
    z->parent = y;
    s.ptr += 1;

    if(y == nullptr) {
      _root = z;
      s.ptr += 1;
    } else {
      s.cmp += 1;
      if(z->key < y->key) {
        y->left = z;
        s.ptr += 1;
      } else {
        y->right = z;
        s.ptr += 1;
      }
    }
  }

  BST_Node *recursiveSearch(const int key, Stats &s) const {
    return _recursive_search(_root, key, s);
  }

  BST_Node *iterativeSearch(const int key, Stats &s) {
    BST_Node *x = _root;
    s.ptr += 1;

    while(x != nullptr) {
      s.cmp += 1;
      if(key == x->key) {
        break;
      }

      s.cmp += 1;
      if(key < x->key) {
        x = x->left;
        s.ptr += 1;
      } else {
        x = x->right;
        s.ptr += 1;
      }
    }

    return x;
  }

  void deleteNode(BST_Node *node, Stats &s) {
    if(node != nullptr) {
      BST_Node *unlinked = _delete_node(node, s);
      delete unlinked;
    }
  }

  void deleteKey(const int key, Stats &s) {
    BST_Node *node = recursiveSearch(key, s);

    if (node != nullptr) {
      BST_Node *unlinked = _delete_node(node, s);
      delete unlinked;
    }
  }

  void print() const {
    if (_root == nullptr) {
      printf("[Tree is empty]\n");
      return;
    }
    _printTree(_root, "", 0);
  }
};

#endif // BST_HPP
