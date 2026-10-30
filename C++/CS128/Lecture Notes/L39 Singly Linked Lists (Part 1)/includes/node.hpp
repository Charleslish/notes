#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
  T data;
  Node<T>* next = nullptr;
  Node(T data) : data(data) {}
};

#endif
