#include <iostream>

#include "tide_log.hpp"

int main() {
  constexpr unsigned int kReadingCount = 5;
  constexpr int kReadings[kReadingCount] = {142, 98, -12, 35, 160};

  TideLog log = MakeLog(2);
  for (unsigned int i = 0; i < kReadingCount; ++i) {
    InsertAt(log, log.size, kReadings[i]);
    std::cout << "size " << log.size << " capacity " << log.capacity
              << std::endl;
  }

  const bool kInserted = InsertAt(log, 1, 120);
  std::cout << "InsertAt(log, 1, 120) returned "
            << (kInserted ? "true" : "false") << std::endl;

  std::cout << "heights:";
  for (unsigned int i = 0; i < log.size; ++i) {
    std::cout << " " << log.heights[i];
  }
  std::cout << std::endl;

  Release(log);
  std::cout << "after Release: size " << log.size << " capacity "
            << log.capacity << std::endl;

  return 0;
}
