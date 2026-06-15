#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include <stdio.h>
#include <string>

#include "../../zad1/include/BST_Node.hpp"
#include "../../zad1/include/Stats.hpp"

class SplayTree {
private:
  BST_Node *_root;

  void _left_rotate(BST_Node *x, Stats &s) {
    BST_Node *y = x->right;
    s.ptr += 1;
    if (y != nullptr) {
      x->right = y->left;
      s.ptr += 1;
      if (y->left != nullptr) {
        y->left->parent = x;
        s.ptr += 1;
      }
      y->parent = x->parent;
      s.ptr += 1;
      if (x->parent == nullptr) {
        _root = y;
        s.ptr += 1;
      } else if (x == x->parent->left) {
        x->parent->left = y;
        s.ptr += 1;
      } else {
        x->parent->right = y;
        s.ptr += 1;
      }
      y->left = x;
      s.ptr += 1;
      x->parent = y;
      s.ptr += 1;
    }
  }

  void _right_rotate(BST_Node *x, Stats &s) {
    BST_Node *y = x->left;
    s.ptr += 1;
    if (y != nullptr) {
      x->left = y->right;
      s.ptr += 1;
      if (y->right != nullptr) {
        y->right->parent = x;
        s.ptr += 1;
      }
      y->parent = x->parent;
      s.ptr += 1;
      if (x->parent == nullptr) {
        _root = y;
        s.ptr += 1;
      } else if (x == x->parent->right) {
        x->parent->right = y;
        s.ptr += 1;
      } else {
        x->parent->left = y;
        s.ptr += 1;
      }
      y->right = x;
      s.ptr += 1;
      x->parent = y;
      s.ptr += 1;
    }
  }

  void _splay(BST_Node *x, Stats &s) {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
      s.ptr += 1;

      if (x->parent->parent == nullptr) {
        s.ptr += 1;
        if (x == x->parent->left) {
          s.ptr += 1;
          _right_rotate(x->parent, s);
        } else {
          s.ptr += 1;
          _left_rotate(x->parent, s);
        }
      } else {
        s.ptr += 1;
        BST_Node *p = x->parent;
        BST_Node *g = p->parent;
        s.ptr += 2;

        if (x == p->left && p == g->left) {
          s.ptr += 2;
          _right_rotate(g, s);
          _right_rotate(p, s);
        } else if (x == p->right && p == g->right) {
          s.ptr += 2;
          _left_rotate(g, s);
          _left_rotate(p, s);
        } else if (x == p->right && p == g->left) {
          s.ptr += 2;
          _left_rotate(p, s);
          _right_rotate(g, s);
        } else {
          s.ptr += 2;
          _right_rotate(p, s);
          _left_rotate(g, s);
        }
      }
    }
  }

  int _height(BST_Node *node) const {
    if (node == nullptr) return 0;
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
  SplayTree() : _root(nullptr) {}
  SplayTree(const int key) : _root(new BST_Node(key)) {}

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

    _splay(z, s);
  }

  BST_Node *iterativeSearch(const int key, Stats &s) {
    BST_Node *x = _root;
    BST_Node *last = nullptr;
    s.ptr += 2;

    while(x != nullptr) {
      last = x;
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

    if (last != nullptr) {
      _splay(last, s);
    }

    if (_root != nullptr && _root->key == key) {
        return _root;
    }
    return nullptr;
  }

  void deleteKey(const int key, Stats &s) {
    if (_root == nullptr) return;

    BST_Node *node = iterativeSearch(key, s);

    if (node != nullptr) {
      BST_Node *left_subtree = _root->left; s.ptr++;
      BST_Node *right_subtree = _root->right; s.ptr++;

      if (left_subtree == nullptr) {
        _root = right_subtree; s.ptr++;
        if (_root != nullptr) { _root->parent = nullptr; s.ptr++; }
      } else if (right_subtree == nullptr) {
        _root = left_subtree; s.ptr++;
        if (_root != nullptr) { _root->parent = nullptr; s.ptr++; }
      } else {
        left_subtree->parent = nullptr; s.ptr++;
        _root = left_subtree; s.ptr++;

        BST_Node *max_left = _root; s.ptr++;
        while (max_left->right != nullptr) {
            max_left = max_left->right; s.ptr += 2;
        }

        _splay(max_left, s);

        _root->right = right_subtree; s.ptr++;
        right_subtree->parent = _root; s.ptr++;
      }
      delete node;
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

#endif // SPLAY_TREE_HPP
