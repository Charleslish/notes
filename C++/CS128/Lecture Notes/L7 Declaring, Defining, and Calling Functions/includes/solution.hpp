#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// Returns the whole minutes of pumping needed for the tank to hold at least
// capacity liters, filling at rate liters per minute; a partly used minute
// counts as a full minute. A tank already at or above capacity needs 0
// minutes. rate is always at least 1.
// MinutesToFill(0, 14, 4) returns 4. MinutesToFill(12, 12, 4) returns 0.
int MinutesToFill(int level, int capacity, int rate);

// Returns the vine's new-leaf count on the given day: day 0 grows first
// leaves, day 1 grows second leaves, and every later day grows the sum of
// the previous two days. day is 0 through 30; first and second are 0
// through 10.
// GrowthOn(2, 4, 7) returns 11. GrowthOn(0, 4, 7) returns 4.
int GrowthOn(int day, int first, int second);

// Returns whether the two moisture readings differ by at most tolerance,
// in either direction. tolerance is never negative.
// ReadingsAgree(10, 13, 3) returns true. ReadingsAgree(10, 14, 3) returns
// false.
bool ReadingsAgree(int first_reading, int second_reading, int tolerance);

#endif
