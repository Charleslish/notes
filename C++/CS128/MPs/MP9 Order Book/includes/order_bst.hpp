#ifndef ORDER_BST_HPP_
#define ORDER_BST_HPP_

#include "tnode.hpp"
#include "utilities.hpp"

class OrderBST {
 public:
  OrderBST() = default;
  ~OrderBST();
  OrderBST(const OrderBST& rhs);
  OrderBST& operator=(const OrderBST& rhs);

  void Insert(TNode<Order>* node);
  TNode<Order>* FindMin() const;
  TNode<Order>* FindMax() const;
  void Remove(TNode<Order>* node);
  TNode<Order>* FindById(unsigned int order_id) const;
  bool IsEmpty() const;

 private:
  TNode<Order>* root_ = nullptr;
  static void Clear(TNode<Order>* node);
  static TNode<Order>* Copy(TNode<Order>* node, TNode<Order>* parent);
  static TNode<Order>* Search(TNode<Order>* node, unsigned int id);
  void Replace(TNode<Order>* node, TNode<Order>* replacement);
};

#endif  // ORDER_BST_HPP_
