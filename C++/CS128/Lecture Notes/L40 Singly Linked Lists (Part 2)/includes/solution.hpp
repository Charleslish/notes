#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <stdexcept>

#include "node.hpp"

template <typename T>
class PriorityQueue {
 public:
  PriorityQueue() = default;
  PriorityQueue(const PriorityQueue<T>& rhs) = delete;
  PriorityQueue<T>& operator=(const PriorityQueue<T>& rhs) = delete;
  ~PriorityQueue();

  void Enqueue(const T& data);
  T Dequeue();

 private:
  Node<T>* head_ = nullptr;
};

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
  Node<T>* current = head_;
  while (current != nullptr) {
    Node<T>* next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
}

template <typename T>
void PriorityQueue<T>::Enqueue(const T& data) {
  Node<T>* new_node = new Node<T>(data);
  if (head_ == nullptr || data < head_->data) {
    new_node->next = head_;
    head_ = new_node;
    return;
  }

  Node<T>* current = head_;
  while (current->next != nullptr && current->next->data <= data) {
    current = current->next;
  }
  new_node->next = current->next;
  current->next = new_node;
}

template <typename T>
T PriorityQueue<T>::Dequeue() {
  if (head_ == nullptr) {
    throw std::runtime_error("PriorityQueue is empty");
  }
  Node<T>* old_head = head_;
  T value = old_head->data;
  head_ = old_head->next;
  delete old_head;
  return value;
}

#endif
