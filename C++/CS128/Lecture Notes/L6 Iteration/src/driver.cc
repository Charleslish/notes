#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kFirstSerial = 3;
  constexpr int kLastSerial = 10;
  constexpr int kStep = 4;
  constexpr int kSerial = 9875;

  std::cout << "batch signature: "
            << BatchSignature(kFirstSerial, kLastSerial, kStep) << std::endl;
  std::cout << "digit sum: " << DigitSum(kSerial) << std::endl;
  std::cout << "checksum folds: " << ChecksumFolds(kSerial) << std::endl;

  return 0;
}
