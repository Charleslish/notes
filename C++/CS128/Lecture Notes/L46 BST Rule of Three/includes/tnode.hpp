#ifndef TNODE_HPP
#define TNODE_HPP

template <typename T>
struct TNode {
  T value;
  TNode<T>* left = nullptr;
  TNode<T>* right = nullptr;
  TNode<T>* parent = nullptr;
  TNode(T value);
};

template <typename T>
TNode<T>::TNode(T value) : value(value) {}

#endif
