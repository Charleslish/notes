#ifndef GRANDPARENT_BST_HPP
#define GRANDPARENT_BST_HPP
#include <iostream>
#include "tnode.hpp"
template <typename T>
class GrandparentBST {
 public:
  GrandparentBST() = default;
  ~GrandparentBST();
  GrandparentBST(const GrandparentBST& other) = delete;
  GrandparentBST& operator=(const GrandparentBST& other) = delete;
  void InsertWithGrandparent(const T& value);
  void PrintTree() const;
 private:
  TNode<T>* root_ = nullptr;
  void Clear(TNode<T>* node);
  void PrintTree(TNode<T>* node, int depth) const;
};
template <typename T>
void GrandparentBST<T>::InsertWithGrandparent(const T& value) {
  TNode<T>* new_node = new TNode<T>(value);
  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }
  TNode<T>* current = root_;
  TNode<T>* parent = nullptr;
  TNode<T>* grandparent = nullptr;
  while (current != nullptr) {
    grandparent = parent;
    parent = current;
    if (value < current->value)
      current = current->left;
    else
      current = current->right;
  }
  new_node->grandparent = grandparent;
  if (value < parent->value)
    parent->left = new_node;
  else
    parent->right = new_node;
}
template <typename T>
void GrandparentBST<T>::PrintTree() const { PrintTree(root_, 0); }
template <typename T>
void GrandparentBST<T>::PrintTree(TNode<T>* node, int depth) const {
  if (node == nullptr) return;
  PrintTree(node->right, depth + 1);
  for (int i = 0; i < depth; ++i) std::cout << "  ";
  std::cout << node->value << std::endl;
  PrintTree(node->left, depth + 1);
}
template <typename T>
void GrandparentBST<T>::Clear(TNode<T>* node) {
  if (node == nullptr) return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}
template <typename T>
GrandparentBST<T>::~GrandparentBST() { Clear(root_); }
#endif
