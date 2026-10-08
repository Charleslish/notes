#include <iostream>

#include "frame_offsets.hpp"

int main() {
  constexpr unsigned int kIntSize = 4;
  constexpr unsigned int kNoOffset = 0;
  constexpr unsigned int kNoSize = 0;
  constexpr unsigned int kEveningPickupsOffset = 8;

  FrameOffsets frame;
  std::cout << "add morning_pickups: "
            << frame.AddObject("morning_pickups", kIntSize) << std::endl;
  std::cout << "add evening_pickups: "
            << frame.AddObject("evening_pickups", kIntSize) << std::endl;
  std::cout << "add kMorningMinutes: "
            << frame.AddObject("kMorningMinutes", kIntSize) << std::endl;
  std::cout << "add kEveningMinutes: "
            << frame.AddObject("kEveningMinutes", kIntSize) << std::endl;

  unsigned int offset = kNoOffset;
  const bool kFound = frame.OffsetOf("kMorningMinutes", &offset);
  std::cout << "offset of kMorningMinutes: " << kFound << ", fp-" << offset
            << std::endl;

  const FrameObject* const kAtOffset = frame.ObjectAt(kEveningPickupsOffset);
  if (kAtOffset != nullptr) {
    std::cout << "object at fp-" << kEveningPickupsOffset << ": "
              << kAtOffset->name << std::endl;
  } else {
    std::cout << "no object at fp-" << kEveningPickupsOffset << std::endl;
  }

  unsigned int size = kNoSize;
  const bool kSizeKnown = frame.FrameSize(&size);
  std::cout << "frame size: " << kSizeKnown << ", " << size << " bytes"
            << std::endl;

  std::cout << "add session_minutes: "
            << frame.AddRunTimeSized("session_minutes") << std::endl;
  size = kNoSize;
  const bool kSizeStillKnown = frame.FrameSize(&size);
  std::cout << "frame size: " << kSizeStillKnown << ", " << size << " bytes"
            << std::endl;
  return 0;
}
