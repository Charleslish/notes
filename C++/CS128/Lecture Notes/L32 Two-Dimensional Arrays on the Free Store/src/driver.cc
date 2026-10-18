#include <iostream>

#include "vineyard.hpp"

int main() {
  constexpr unsigned int kRows = 3;
  constexpr unsigned int kVines = 4;
  constexpr unsigned int kMoreRows = 5;
  constexpr unsigned int kFewerVines = 2;
  constexpr unsigned int kRow = 1;
  constexpr unsigned int kVine = 1;
  constexpr int kGrams = 2350;

  Vineyard hillside(kRows, kVines);
  std::cout << "rows " << hillside.Rows() << ", vines per row "
            << hillside.VinesPerRow() << std::endl;

  const bool kRecorded = hillside.Record(kRow, kVine, kGrams);
  std::cout << "record " << kGrams << " at row " << kRow << ", vine " << kVine
            << ": " << kRecorded << std::endl;

  int grams = 0;
  const bool kFound = hillside.YieldAt(kRow, kVine, grams);
  std::cout << "yield at row " << kRow << ", vine " << kVine << ": " << kFound
            << ", grams " << grams << std::endl;

  const bool kResized = hillside.Resize(kMoreRows, kFewerVines);
  std::cout << "resize to " << kMoreRows << " by " << kFewerVines << ": "
            << kResized << ", rows " << hillside.Rows() << ", vines per row "
            << hillside.VinesPerRow() << std::endl;
  return 0;
}
