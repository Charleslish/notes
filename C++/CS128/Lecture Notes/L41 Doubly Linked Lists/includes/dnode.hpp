#ifndef DNODE_HPP
#define DNODE_HPP

template <typename T>
struct DNode {
  T data;
  DNode<T>* next = nullptr;
  DNode<T>* prev = nullptr;

  DNode(T data) : data(data) {}
  DNode(T data, DNode<T>* next, DNode<T>* prev)
      : data(data), next(next), prev(prev) {}
};

#endif
