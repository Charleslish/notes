#include <iostream>
#include <sstream>

#include "solution.hpp"

int main() {
  unsigned long long card_number = 1234567890123456ULL; // ULL: unsigned long long
  std::string expected = "9H3G5D9B1C5F7F1I597";

  std::cout << "expected: " << expected << std::endl;
  std::cout << "actual:   ";
  EncryptCreditCard(card_number);
  std::cout << std::endl;

  return 0;
}
