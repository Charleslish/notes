#include "solution.hpp"

void IntArray::PushBack(int value) {
  if (size_ > capacity_) {
    capacity_ *= 2;
    int* temp = new int[capacity_];
    for (unsigned int i = 0; i < capacity_; ++i) {
      temp[i] = array_[i];
    }
    delete[] array_;
    array_ = temp;

  }
  array_[size_] = value;
  size_ += 1;
}