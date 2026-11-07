#ifndef SEGMENT_HPP
#define SEGMENT_HPP

struct Segment {
  unsigned int row = 0;
  unsigned int col = 0;
  unsigned int original_index = 0;
  Segment* prev = nullptr;
  Segment* next = nullptr;
};

#endif
