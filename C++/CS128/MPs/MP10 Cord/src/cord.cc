#include "cord.hpp"

#include <stdexcept>

Cord::Cord(const std::string_view& sv) {
  if (sv.empty())
    throw std::invalid_argument("Empty cord");
  length_ = static_cast<unsigned int>(sv.size());
  data_ = new char[length_ + 1];
  for (unsigned int index = 0; index < length_; ++index)
    data_[index] = sv[index];
  data_[length_] = '\0';
}

Cord::~Cord() {
  delete[] data_;
}

void Cord::WriteTo(char* destination) const {
  if (left_.Get() != nullptr) {
    left_->WriteTo(destination);
    right_->WriteTo(destination + left_->length_);
  }
  else
    for (unsigned int index = 0; index < length_; ++index)
      destination[index] = data_[index];
}

SharedPointer<char> Cord::ToString() const {
  SharedPointer<char> output(new char[length_ + 1], kSharedPointerType::kArray);
  WriteTo(output.Get());
  output.Get()[length_] = '\0';
  return output;
}
