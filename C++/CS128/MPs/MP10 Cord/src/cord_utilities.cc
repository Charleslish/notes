#include "cord_utilities.hpp"

#include <stdexcept>

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                               SharedPointer<Cord> right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr)
    throw std::invalid_argument("Null cord operand");
  SharedPointer<Cord> result(new Cord);
  result->left_ = left_cord;
  result->right_ = right_cord;
  result->length_ = left_cord->Length() + right_cord->Length();
  return result;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                             unsigned int lower_idx,
                             unsigned int upper_idx) {
  if (curr_cord.Get() == nullptr || lower_idx >= upper_idx ||
      upper_idx > curr_cord->Length())
    throw std::out_of_range("Invalid cord substring");
  if (lower_idx == 0 && upper_idx == curr_cord->Length())
    return curr_cord;
  SharedPointer<Cord> left = curr_cord->Left();
  if (left.Get() == nullptr)
    return SharedPointer<Cord>(new Cord(std::string_view(
        curr_cord->Data().data() + lower_idx, upper_idx - lower_idx)));
  unsigned int split = left->Length();
  if (upper_idx <= split)
    return SubString(left, lower_idx, upper_idx);
  if (lower_idx >= split)
    return SubString(curr_cord->Right(), lower_idx - split, upper_idx - split);
  return ConcatCords(SubString(left, lower_idx, split),
                     SubString(curr_cord->Right(), 0, upper_idx - split));
}
