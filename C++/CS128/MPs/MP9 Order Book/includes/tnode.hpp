#ifndef TNODE_HPP_
#define TNODE_HPP_

template <typename T>
struct TNode {
  T value;
  TNode* left = nullptr;
  TNode* right = nullptr;
  TNode* parent = nullptr;
  TNode(const T& val) : value(val) {}
};

#endif  // TNODE_HPP_
