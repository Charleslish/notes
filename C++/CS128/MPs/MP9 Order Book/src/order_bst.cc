#include "order_bst.hpp"

void OrderBST::Clear(TNode<Order>* node) {
  if (node == nullptr)
    return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

TNode<Order>* OrderBST::Copy(TNode<Order>* node, TNode<Order>* parent) {
  if (node == nullptr)
    return nullptr;
  TNode<Order>* result = new TNode<Order>(node->value);
  result->parent = parent;
  result->left = Copy(node->left, result);
  result->right = Copy(node->right, result);
  return result;
}

OrderBST::~OrderBST() { Clear(root_); }
OrderBST::OrderBST(const OrderBST& rhs) { root_ = Copy(rhs.root_, nullptr); }
OrderBST& OrderBST::operator=(const OrderBST& rhs) {
  if (this == &rhs)
    return *this;
  Clear(root_);
  root_ = Copy(rhs.root_, nullptr);
  return *this;
}

void OrderBST::Insert(TNode<Order>* node) {
  TNode<Order>* parent = nullptr;
  TNode<Order>* current = root_;
  while (current != nullptr) {
    parent = current;
    current = node->value < current->value ? current->left : current->right;
  }
  node->parent = parent;
  if (parent == nullptr)
    root_ = node;
  else if (node->value < parent->value)
    parent->left = node;
  else
    parent->right = node;
}

TNode<Order>* OrderBST::FindMin() const {
  TNode<Order>* node = root_;
  while (node != nullptr && node->left != nullptr)
    node = node->left;
  return node;
}
TNode<Order>* OrderBST::FindMax() const {
  TNode<Order>* node = root_;
  while (node != nullptr && node->right != nullptr)
    node = node->right;
  return node;
}
void OrderBST::Replace(TNode<Order>* node, TNode<Order>* replacement) {
  if (node->parent == nullptr)
    root_ = replacement;
  else if (node == node->parent->left)
    node->parent->left = replacement;
  else
    node->parent->right = replacement;
  if (replacement != nullptr)
    replacement->parent = node->parent;
}
void OrderBST::Remove(TNode<Order>* node) {
  if (node->left == nullptr)
    Replace(node, node->right);
  else if (node->right == nullptr)
    Replace(node, node->left);
  else {
    TNode<Order>* successor = node->right;
    while (successor->left != nullptr)
      successor = successor->left;
    if (successor->parent != node) {
      Replace(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }
    Replace(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
  }
  delete node;
}
TNode<Order>* OrderBST::Search(TNode<Order>* node, unsigned int id) {
  if (node == nullptr || node->value.order_id == id)
    return node;
  TNode<Order>* found = Search(node->left, id);
  if (found != nullptr)
    return found;
  return Search(node->right, id);
}
TNode<Order>* OrderBST::FindById(unsigned int order_id) const {
  return Search(root_, order_id);
}
bool OrderBST::IsEmpty() const { return root_ == nullptr; }
