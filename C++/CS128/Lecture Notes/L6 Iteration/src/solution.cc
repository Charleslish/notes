#include "solution.hpp"

int BatchSignature(int first, int last, int step) {
  // TODO: Sum the serials first, first + step, first + 2 * step, ... for
  // every serial that is at most last.
  int sum = 0, number = first;
  while (number <= last){
    sum += number;
    number += step;
  }
  return sum;
}

int DigitSum(int serial) {
  // TODO: Sum the decimal digits of serial with a loop that applies % and
  // / by a named digit-base constant (a bare 10 fails the clear-code
  // checks).
  int sum = 0;
  const int kDecimal = 10;
  while (serial > 0){
    sum += serial % kDecimal;
    serial /= kDecimal;
  }
  return sum;
}

int ChecksumFolds(int serial) {
  // TODO: Count how many times the digit sum must be applied before the
  // value is a single digit. Calling your DigitSum is allowed.
  int count = 0;
  const int kDecimal = 10;
  while (serial >= kDecimal){
    serial = DigitSum(serial);
    ++count;
  } 
  return count;
}
