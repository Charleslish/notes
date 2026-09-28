#include "solution.hpp"

bool IsValidDisplay(const std::string& display) {
  if(display.empty()) return false;
  for(unsigned int i = 0; i < display.size(); ++i){
    if(display[i] < '0' || display[i] > '9')
      return false;
  }
  return true;
}

std::string Advance(const std::string& display) {
  std::string advanced = display;
  for (int i = static_cast<int>(advanced.size()-1); i >= 0; --i) { 
    if (advanced[i] < '9'){ 
      advanced[i]++; 
      return advanced;
    }
    advanced[i] = '0';
  }
  return advanced;
}

int ClicksBetween(const std::string& before, const std::string& after) {
  std::string copy = before;
  int total = 0;
  while(copy != after){
    copy = Advance(copy);
    total++;
  }
  return total;
}
