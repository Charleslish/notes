#include "frame_stack.hpp"

#include <vector>

bool FrameStack::Push(const std::vector<int>& arguments, unsigned int local_count) {
  const unsigned int kValueCount = static_cast<unsigned int>(arguments.size()) + local_count;
  if (!Fits(kValueCount))
    return false;
  const unsigned int kStart = StackPointer();
  frames_[depth_].start = kStart;
  frames_[depth_].parameter_count = static_cast<unsigned int>(arguments.size());
  frames_[depth_].local_count = local_count;
  for (unsigned int i = 0; i < arguments.size(); ++i)
    values_[kStart + i] = arguments[i];
  ++depth_;
  return true;
}

bool FrameStack::Pop() {
  if (depth_ == 0)
    return false;
  --depth_;
  return true;
}

const Frame* FrameStack::Top() const {
  if (depth_ == 0)
    return nullptr;
  return &frames_[depth_ - 1];
}

bool FrameStack::Read(unsigned int position, int* value) const {
  if (depth_ == 0 || value == nullptr)
    return false;
  const Frame* frame = Top();
  const unsigned int kValueCount = frame->parameter_count + frame->local_count;
  if (position >= kValueCount) 
    return false;
  *value = values_[frame->start + position];
  return true;
}

bool FrameStack::Write(unsigned int position, int value) {
  if (depth_ == 0)
    return false;
  const Frame* frame = Top();
  const unsigned int kValueCount = frame->parameter_count + frame->local_count;
  if (position >= kValueCount) 
    return false;
  values_[frame->start + position] = value;
  return true;
}

unsigned int FrameStack::StackPointer() const {
  if (depth_ == 0)
    return 0;
  const Frame* frame = Top();
  return frame->start + frame->parameter_count + frame->local_count;
}

unsigned int FrameStack::Depth() const {
  return depth_;
}

bool FrameStack::Fits(unsigned int value_count) const {
  if (depth_ >= kMaxFrames)
    return false;
  return StackPointer() + value_count <= kValueCount;
}