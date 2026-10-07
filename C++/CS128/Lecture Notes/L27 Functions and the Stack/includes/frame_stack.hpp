#ifndef FRAME_STACK_HPP
#define FRAME_STACK_HPP

#include <vector>

constexpr unsigned int kValueCount = 16;
constexpr unsigned int kMaxFrames = 8;

struct Frame {
  unsigned int start = 0;
  unsigned int parameter_count = 0;
  unsigned int local_count = 0;
};

class FrameStack {
 public:
  FrameStack() = default;
  bool Push(const std::vector<int>& arguments, unsigned int local_count);
  bool Pop();
  const Frame* Top() const;
  bool Read(unsigned int position, int* value) const;
  bool Write(unsigned int position, int value);
  unsigned int StackPointer() const;
  unsigned int Depth() const;

 private:
  bool Fits(unsigned int value_count) const;
  int values_[kValueCount]{};
  Frame frames_[kMaxFrames]{};
  unsigned int depth_ = 0;
};

#endif
