#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include "node.hpp"

template <typename T>
class SinglyLinkedList {
 public:
  SinglyLinkedList() = default;
  ~SinglyLinkedList();
  void PushBack(const T& value);
  void PushFront(const T& value);

 private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
};

// Provided: destructor (deletes every node in the list)
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  Node<T>* current = head_;
  while (current != nullptr) {
    Node<T>* next = current->next;
    delete current;
    current = next;
  }
}

template <typename T>
void SinglyLinkedList<T>::PushBack(const T& value) {
  Node<T>* new_node = new Node<T>(value);
  if (tail_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    return;
  }
  tail_->next = new_node;
  tail_ = new_node;
}

template <typename T>
void SinglyLinkedList<T>::PushFront(const T& value) {
  Node<T>* new_node = new Node<T>(value);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    return;
  }
  new_node->next = head_;
  head_ = new_node;
}

#endif
