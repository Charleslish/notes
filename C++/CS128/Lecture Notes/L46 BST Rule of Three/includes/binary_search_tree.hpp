#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

#include "tnode.hpp"

template <typename T>
class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  ~BinarySearchTree();

  BinarySearchTree(const BinarySearchTree& other);
  BinarySearchTree& operator=(const BinarySearchTree& other);

  void Insert(const T& value);
  void PrintTree() const;

 private:
  TNode<T>* root_ = nullptr;

  void PrintTree(TNode<T>* node, int depth) const;

  void Clear(TNode<T>* node);
  TNode<T>* CopyTree(TNode<T>* node, TNode<T>* parent) const;
};

template <typename T>
void BinarySearchTree<T>::Clear(TNode<T>* node) {
  if (node == nullptr)
    return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear(root_);
}

template <typename T>
TNode<T>* BinarySearchTree<T>::CopyTree(TNode<T>* node, TNode<T>* parent) const {
  if (node == nullptr)
    return nullptr;
  TNode<T>* copy = new TNode<T>(node->value);
  copy->parent = parent;
  try {
    copy->left = CopyTree(node->left, copy);
    copy->right = CopyTree(node->right, copy);
  } catch (...) {
    const_cast<BinarySearchTree<T>*>(this)->Clear(copy);
    throw;
  }
  return copy;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) {
  root_ = CopyTree(other.root_, nullptr);
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
  if (this == &other)
    return *this;
  Clear(root_);
  root_ = nullptr;
  root_ = CopyTree(other.root_, nullptr);
  return *this;
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

#endif
