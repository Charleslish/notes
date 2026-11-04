#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include "dnode.hpp"

template <typename T>
class DoublyLinkedList {
 public:
  DoublyLinkedList() = default;
  ~DoublyLinkedList();
  void InsertSorted(const T& value);

 private:
  DNode<T>* head_ = nullptr;
  DNode<T>* tail_ = nullptr;
};

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  DNode<T>* current = head_;
  while (current != nullptr) {
    DNode<T>* next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::InsertSorted(const T& value) {
  DNode<T>* new_node = new DNode<T>(value);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    return;
  }

  if (value < head_->data) {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
    return;
  }

  if (value >= tail_->data) {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
    return;
  }

  DNode<T>* current = head_;
  while (current != nullptr && current->data <= value) {
    current = current->next;
  }

  new_node->next = current;
  new_node->prev = current->prev;
  current->prev->next = new_node;
  current->prev = new_node;
}

#endif
