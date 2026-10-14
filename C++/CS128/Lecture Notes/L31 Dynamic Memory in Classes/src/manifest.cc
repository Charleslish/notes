#include "manifest.hpp"

Manifest::Manifest(unsigned int size) : size_(size) {
  vehicles_ = new int[size_]{};
}

Manifest::Manifest(const Manifest& other) : size_(other.size_) {
  vehicles_ = new int[size_]{};
  for (unsigned int i = 0; i < size_; ++i) 
    vehicles_[i] = other.vehicles_[i];
}

Manifest& Manifest::operator=(const Manifest& other) {
  int* copied = new int[other.size_]{};
  for (unsigned int i = 0; i < other.size_; ++i)
    copied[i] = other.vehicles_[i];
  delete[] vehicles_;
  vehicles_ = copied;
  size_ = other.size_;
  return *this;
}

Manifest::~Manifest() {
  delete[] vehicles_;
}

unsigned int Manifest::Size() const {
  return size_;
}

bool Manifest::Load(unsigned int slot, int vehicle) {
  if (slot >= size_ || vehicles_[slot] != 0)
    return false;
  vehicles_[slot] = vehicle;
  return true;
}

bool Manifest::VehicleAt(unsigned int slot, int& vehicle) const {
  if (slot >= size_ || vehicles_[slot] == 0)
    return false;
  vehicle = vehicles_[slot];
  return true;
}
