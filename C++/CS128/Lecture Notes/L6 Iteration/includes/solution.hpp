#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// Returns the sum of the serials first, first + step, first + 2 * step, ...
// for every serial that is at most last. When first > last, no serial is
// scanned and the result is 0. step is always at least 1.
// BatchSignature(3, 10, 4) returns 10. BatchSignature(8, 3, 2) returns 0.
int BatchSignature(int first, int last, int step);

// Returns the sum of the decimal digits of serial. serial is never negative.
// DigitSum(305) returns 8. DigitSum(0) returns 0.
int DigitSum(int serial);

// Returns how many times the digit sum must be applied to serial before the
// value is a single digit (less than 10). A serial that is already a single
// digit needs 0 folds. serial is never negative.
// ChecksumFolds(9875) returns 3 (9875 -> 29 -> 11 -> 2).
// ChecksumFolds(9) returns 0.
int ChecksumFolds(int serial);

#endif
