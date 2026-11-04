#ifndef NODE_HPP
#define NODE_HPP

struct Node {
  char data = '\0';         // NOLINT
  Node* next = nullptr;     // NOLINT
  Node(char data): data(data) {}
  Node(char data, Node* next): data(data), next(next) {}
};

#endif