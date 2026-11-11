#ifndef FIND_BST_HPP
#define FIND_BST_HPP

#include <iostream>
#include <vector>

#include "tnode.hpp"

template <typename T>
class FindBST {
 public:
  FindBST() = default;
  ~FindBST();

  FindBST(const FindBST& other) = delete;
  FindBST& operator=(const FindBST& other) = delete;

  void Insert(const T& value);
  void PrintTree() const;

  const T* Find(const T& target) const;
  const T* FindMin() const;
  const T* FindMax() const;
  int Height() const;
  std::vector<T> InorderTraversal() const;
  std::vector<T> PreorderTraversal() const;
  std::vector<T> PostorderTraversal() const;

 private:
  TNode<T>* root_ = nullptr;

  void Clear(TNode<T>* node);
  void PrintTree(TNode<T>* node, int depth) const;
  int Height(TNode<T>* node) const;
  void Inorder(TNode<T>* node, std::vector<T>& result) const;
  void Preorder(TNode<T>* node, std::vector<T>& result) const;
  void Postorder(TNode<T>* node, std::vector<T>& result) const;
};

template <typename T>
const T* FindBST<T>::Find(const T& target) const {
  const TNode<T>* current = root_;
  while (current != nullptr) {
    if (target == current->value)
      return &current->value;
    if (target < current->value)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}

template <typename T>
const T* FindBST<T>::FindMin() const {
  const TNode<T>* current = root_;
  if (current == nullptr)
    return nullptr;
  while (current->left != nullptr)
    current = current->left;
  return &current->value;
}

template <typename T>
const T* FindBST<T>::FindMax() const {
  const TNode<T>* current = root_;
  if (current == nullptr)
    return nullptr;
  while (current->right != nullptr)
    current = current->right;
  return &current->value;
}

template <typename T>
int FindBST<T>::Height() const {
  return Height(root_);
}

template <typename T>
int FindBST<T>::Height(TNode<T>* node) const {
  if (node == nullptr)
    return -1;
  const int left_height = Height(node->left);
  const int right_height = Height(node->right);
  return 1 + (left_height > right_height ? left_height : right_height);
}

template <typename T>
std::vector<T> FindBST<T>::InorderTraversal() const {
  std::vector<T> result;
  Inorder(root_, result);
  return result;
}

template <typename T>
void FindBST<T>::Inorder(TNode<T>* node, std::vector<T>& result) const {
  if (node == nullptr)
    return;
  Inorder(node->left, result);
  result.push_back(node->value);
  Inorder(node->right, result);
}

template <typename T>
std::vector<T> FindBST<T>::PreorderTraversal() const {
  std::vector<T> result;
  Preorder(root_, result);
  return result;
}

template <typename T>
void FindBST<T>::Preorder(TNode<T>* node, std::vector<T>& result) const {
  if (node == nullptr)
    return;
  result.push_back(node->value);
  Preorder(node->left, result);
  Preorder(node->right, result);
}

template <typename T>
std::vector<T> FindBST<T>::PostorderTraversal() const {
  std::vector<T> result;
  Postorder(root_, result);
  return result;
}

template <typename T>
void FindBST<T>::Postorder(TNode<T>* node, std::vector<T>& result) const {
  if (node == nullptr)
    return;
  Postorder(node->left, result);
  Postorder(node->right, result);
  result.push_back(node->value);
}

template <typename T>
void FindBST<T>::Insert(const T& value) {
  TNode<T>* new_node = new TNode<T>(value);
  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }
  TNode<T>* current = root_;
  TNode<T>* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  if (value < parent->value) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
}

template <typename T>
void FindBST<T>::PrintTree() const {
  if (root_ == nullptr) {
    std::cout << "(empty tree)" << std::endl;
    return;
  }
  PrintTree(root_, 0);
}

template <typename T>
void FindBST<T>::PrintTree(TNode<T>* node, int depth) const {
  if (node == nullptr) return;
  PrintTree(node->right, depth + 1);
  for (int i = 0; i < depth; i++) std::cout << "    ";
  std::cout << node->value << std::endl;
  PrintTree(node->left, depth + 1);
}

template <typename T>
void FindBST<T>::Clear(TNode<T>* node) {
  if (node == nullptr) return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename T>
FindBST<T>::~FindBST() {
  Clear(root_);
}

#endif
