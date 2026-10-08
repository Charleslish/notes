#include "frame_offsets.hpp"


bool FrameOffsets::AddObject(const std::string& name, unsigned int size) {
  unsigned int index = 0;
  if (size == 0 || IndexOf(name, &index))
    return false;
  FrameObject object;
  object.name = name;
  object.size = size;
  object.size_known = true;
  objects_.push_back(object);
  return true;
}

bool FrameOffsets::AddRunTimeSized(const std::string& name) {
  unsigned int index = 0;
  if (IndexOf(name, &index))
    return false;
  FrameObject object;
  object.name = name;
  object.size = 0;
  object.size_known = false;
  objects_.push_back(object);
  return true;
}

bool FrameOffsets::OffsetOf(const std::string& name, unsigned int* offset) const {
  if (offset == nullptr)
    return false;
  unsigned int index = 0;
  if (!IndexOf(name, &index) || !OffsetKnown(index))
    return false;
  unsigned int total = 0;
  for (unsigned int i = 0; i <= index; ++i)
    total += objects_[i].size;
  *offset = total;
  return true;
}

const FrameObject* FrameOffsets::ObjectAt(unsigned int offset) const {
  unsigned int current_offset = 0;
  for (unsigned int i = 0; i < objects_.size(); ++i) {
    if (!OffsetKnown(i))
      continue;
    current_offset += objects_[i].size;
    if (current_offset == offset)
      return &objects_[i];
  }
  return nullptr;
}

bool FrameOffsets::FrameSize(unsigned int* size) const {
  if (size == nullptr)
    return false;
  for (unsigned int i = 0; i < objects_.size(); ++i)
    if (!OffsetKnown(i))
      return false;
  unsigned int total = 0;
  for (unsigned int i = 0; i < objects_.size(); ++i)
    total += objects_[i].size;
  *size = total;
  return true;
}

bool FrameOffsets::IndexOf(const std::string& name, unsigned int* index) const {
  for (unsigned int i = 0; i < objects_.size(); ++i) {
    if (objects_[i].name == name) {
      *index = i;
      return true;
    }
  }
  return false;
}

bool FrameOffsets::OffsetKnown(unsigned int index) const {
  if (index >= objects_.size())
    return false;
  for (unsigned int i = 0; i <= index; ++i)
    if (!objects_[i].size_known)
      return false;
  return true;
}