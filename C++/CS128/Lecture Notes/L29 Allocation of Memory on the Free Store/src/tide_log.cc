#include "tide_log.hpp"

TideLog MakeLog(unsigned int capacity) {
  if (capacity==0)
    return TideLog{nullptr, 0, 0};
  TideLog log{new int[capacity], 0, capacity};
  return log;
}

void Reserve(TideLog& log, unsigned int capacity) {
  if (log.capacity >= capacity)
    return;
  TideLog new_log{new int[capacity], log.size, capacity};
  for (unsigned int i = 0; i < log.size; ++i)
    new_log.heights[i] = log.heights[i];
  delete[] log.heights;
  log = new_log;
}

bool InsertAt(TideLog& log, unsigned int index, int height) {
  if (index > log.size)
    return false;
  if (log.size == log.capacity) {
    unsigned int new_capacity = (log.capacity == 0) ? 1 : log.capacity * 2;
    int* new_heights = new int[new_capacity]{};
    for (unsigned int i = 0; i < log.size; ++i) 
      new_heights[i] = log.heights[i];
    delete[] log.heights;
    log.heights = new_heights;
    log.capacity = new_capacity;
  }
  for (unsigned int i = log.size; i > index; --i)
    log.heights[i] = log.heights[i - 1];
  log.heights[index] = height;
  ++log.size;
  return true;
}

void Release(TideLog& log) {
  delete[] log.heights;
  log.heights = nullptr;
  log.size = 0;
  log.capacity = 0;
}
