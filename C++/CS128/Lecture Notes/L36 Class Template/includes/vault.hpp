#ifndef VAULT_HPP
#define VAULT_HPP

#include "artifact.hpp"
#include <stdexcept>

template <typename T>
class Vault {
 public:
  void Store(const T& item);
  T Peek();
  unsigned int GetAccessCount() const;
  bool IsEmpty() const;

 private:
  T item_{};
  bool has_item_ = false;
  unsigned int access_count_ = 0;
};

template <typename T>
void Vault<T>::Store(const T& item) {
  item_ = item;
  has_item_ = true;
}

template <typename T>
T Vault<T>::Peek() {
  if (IsEmpty())
    throw std::runtime_error("Vault is empty");
  access_count_++;
  return item_;
}

template <typename T>
unsigned int Vault<T>::GetAccessCount() const { return access_count_; }

template <typename T>
bool Vault<T>::IsEmpty() const { return !has_item_; }

#endif
