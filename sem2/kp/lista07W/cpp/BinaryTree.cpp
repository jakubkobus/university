#include "BinaryTree.hpp"
#include <iomanip>

template <typename T>
BinaryTree<T>::Node::Node(const T &v) : value(v) {}

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::insertRec(Node *node, const T &value)
{
  if (!node)
    return new Node(value);
  if (value < node->value)
    node->left.reset(insertRec(node->left.release(), value));
  else if (value > node->value)
    node->right.reset(insertRec(node->right.release(), value));
  return node;
}

template <typename T>
void BinaryTree<T>::insert(const T &value)
{
  root.reset(insertRec(root.release(), value));
}

template <typename T>
bool BinaryTree<T>::searchRec(Node *node, const T &value) const
{
  if (!node)
    return false;
  if (value == node->value)
    return true;
  return value < node->value ? searchRec(node->left.get(), value)
                             : searchRec(node->right.get(), value);
}

template <typename T>
bool BinaryTree<T>::search(const T &value) const
{
  return searchRec(root.get(), value);
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::deleteRec(Node *node, const T &value)
{
  if (!node)
    return nullptr;
  if (value < node->value)
    node->left.reset(deleteRec(node->left.release(), value));
  else if (value > node->value)
    node->right.reset(deleteRec(node->right.release(), value));
  else
  {
    if (!node->left)
      return node->right.release();
    if (!node->right)
      return node->left.release();
    Node *min = node->right.get();
    while (min->left)
      min = min->left.get();
    node->value = min->value;
    node->right.reset(deleteRec(node->right.release(), min->value));
  }
  return node;
}

template <typename T>
bool BinaryTree<T>::remove(const T &value)
{
  int before = size();
  root.reset(deleteRec(root.release(), value));
  return size() < before;
}

template <typename T>
void BinaryTree<T>::drawRec(const Node *node, std::ostringstream &oss, int depth) const
{
  if (!node)
    return;
  drawRec(node->right.get(), oss, depth + 1);
  for (int i = 0; i < depth; ++i)
    oss << std::setw(NODE_WIDTH) << " ";
  std::ostringstream valss;
  valss << node->value;
  std::string valueStr = valss.str();
  oss << std::left << std::setw(NODE_WIDTH) << valueStr << "\n";
  drawRec(node->left.get(), oss, depth + 1);
}

template <typename T>
std::string BinaryTree<T>::draw() const
{
  if (!root)
    return "";
  std::ostringstream oss;
  drawRec(root.get(), oss, 0);
  return oss.str();
}

template <typename T>
int BinaryTree<T>::sizeRec(const Node *node) const
{
  if (!node)
    return 0;
  return 1 + sizeRec(node->left.get()) + sizeRec(node->right.get());
}

template <typename T>
int BinaryTree<T>::size() const
{
  return sizeRec(root.get());
}

template <typename T>
bool BinaryTree<T>::isEmpty() const
{
  return !root;
}

template class BinaryTree<int>;
template class BinaryTree<double>;
template class BinaryTree<std::string>;