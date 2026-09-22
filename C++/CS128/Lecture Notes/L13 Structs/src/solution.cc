#include "solution.hpp"



unsigned int CountValid(const std::vector<Reading>& log){
  unsigned int count = 0;
  for (const auto& read : log){
    if(read.is_valid)
      count++;
  }
  return count;
}

Reading BestReading(const std::vector<Reading>& log){
  if(log.empty() || CountValid(log) == 0)
    return {0, 0, false};
  Reading best{};
  bool found = false;
  for (const auto& read : log){
    if(read.is_valid)
      if(!found || read.celsius > best.celsius){
        best = read;
        found = true;
      }
  }
  return best;
}