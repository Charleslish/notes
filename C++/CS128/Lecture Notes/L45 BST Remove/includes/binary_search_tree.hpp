#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

#include "tnode.hpp"

template <typename T>
class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  ~BinarySearchTree();

  BinarySearchTree(const BinarySearchTree& other) = delete;
  BinarySearchTree& operator=(const BinarySearchTree& other) = delete;

  void Insert(const T& value);
  void PrintTree() const;
  void Remove(const T& value);

 private:
  TNode<T>* root_ = nullptr;

  TNode<T>* FindMin(TNode<T>* node) const;
  void Clear(TNode<T>* node);
  void PrintTree(TNode<T>* node, int depth) const;

  TNode<T>* FindNode(const T& value);
  void RemoveLeaf(TNode<T>* node);
  void RemoveOneChild(TNode<T>* node);
  void RemoveTwoChildren(TNode<T>* node);
};

template <typename T>
TNode<T>* BinarySearchTree<T>::FindNode(const T& value) {
  TNode<T>* current = root_;
  while (current != nullptr) {
    if (value == current->value)
      return current;
    if (value < current->value)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}

template <typename T>
void BinarySearchTree<T>::Remove(const T& value) {
  TNode<T>* node = FindNode(value);
  if (node == nullptr)
    return;
  if (node->left == nullptr && node->right == nullptr)
    RemoveLeaf(node);
  else if (node->left == nullptr || node->right == nullptr)
    RemoveOneChild(node);
  else
    RemoveTwoChildren(node);
}

template <typename T>
void BinarySearchTree<T>::RemoveLeaf(TNode<T>* node) {
  if (node->parent == nullptr)
    root_ = nullptr;
  else if (node->parent->left == node)
    node->parent->left = nullptr;
  else
    node->parent->right = nullptr;
  delete node;
}

template <typename T>
void BinarySearchTree<T>::RemoveOneChild(TNode<T>* node) {
  TNode<T>* child = node->left != nullptr ? node->left : node->right;
  child->parent = node->parent;
  if (node->parent == nullptr)
    root_ = child;
  else if (node->parent->left == node)
    node->parent->left = child;
  else
    node->parent->right = child;
  delete node;
}

template <typename T>
void BinarySearchTree<T>::RemoveTwoChildren(TNode<T>* node) {
  TNode<T>* successor = FindMin(node->right);
  if (successor->parent != node) {
    successor->parent->left = successor->right;
    if (successor->right != nullptr)
      successor->right->parent = successor->parent;
    successor->right = node->right;
    node->right->parent = successor;
  }
  successor->left = node->left;
  node->left->parent = successor;
  successor->parent = node->parent;
  if (node->parent == nullptr)
    root_ = successor;
  else if (node->parent->left == node)
    node->parent->left = successor;
  else
    node->parent->right = successor;
  delete node;
}

template <typename T>
TNode<T>* BinarySearchTree<T>::FindMin(TNode<T>* node) const {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T>
void BinarySearchTree<T>::Insert(const T& value) {
  TNode<T>* new_node = new TNode<T>(value);
  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }
  TNode<T>* current = root_;
  TNode<T>* par = nullptr;
  while (current != nullptr) {
    par = current;
    if (value < current->value)
      current = current->left;
    else
      current = current->right;
  }
  new_node->parent = par;
  if (value < par->value)
    par->left = new_node;
  else
    par->right = new_node;
}

template <typename T>
void BinarySearchTree<T>::PrintTree() const {
  if (root_ == nullptr) {
    std::cout << "(empty tree)" << std::endl;
    return;
  }
  PrintTree(root_, 0);
}

template <typename T>
void BinarySearchTree<T>::PrintTree(TNode<T>* node, int depth) const {
  if (node == nullptr) return;
  PrintTree(node->right, depth + 1);
  for (int i = 0; i < depth; i++) std::cout << "    ";
  std::cout << node->value << std::endl;
  PrintTree(node->left, depth + 1);
}

template <typename T>
void BinarySearchTree<T>::Clear(TNode<T>* node) {
  if (node == nullptr) return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear(root_);
}

#endif
