#ifndef FRAME_OFFSETS_HPP
#define FRAME_OFFSETS_HPP

#include <string>
#include <vector>

struct FrameObject {
  std::string name;
  unsigned int size = 0;
  bool size_known = true;
};

class FrameOffsets {
 public:
  FrameOffsets() = default;
  bool AddObject(const std::string& name, unsigned int size);
  bool AddRunTimeSized(const std::string& name);
  bool OffsetOf(const std::string& name, unsigned int* offset) const;
  const FrameObject* ObjectAt(unsigned int offset) const;
  bool FrameSize(unsigned int* size) const;

 private:
  bool IndexOf(const std::string& name, unsigned int* index) const;
  bool OffsetKnown(unsigned int index) const;
  std::vector<FrameObject> objects_;
};

#endif
