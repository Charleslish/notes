#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// Returns the base points plus the points earned from the bonuses, where each
// of bonus_count bonuses is worth bonus_value points.
// TotalPoints(240, 2, 15) returns 270. TotalPoints(250, 0, 15) returns 250.
int TotalPoints(int base, int bonus_count, int bonus_value);

// Returns what remains of total after both penalties are taken off it.
// RemainingPoints(20, 15, 3) returns 2. RemainingPoints(100, 0, 40) returns 60.
int RemainingPoints(int total, int first_penalty, int second_penalty);

// Returns whether the term is open and the point total has reached the
// threshold. IsEligible(true, 250, 250) returns true.
// IsEligible(false, 400, 250) returns false.
bool IsEligible(bool is_open, int points, int threshold);

#endif
