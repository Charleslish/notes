#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// Returns the band a quiz score falls in: 'h' when the score has reached 90,
// 'p' at 70 through 89, 'c' at 50 through 69, and 'a' below 50.
// QuizBand(90) returns 'h'. QuizBand(69) returns 'c'.
char QuizBand(int quiz_score);

// Returns whether the score includes partial credit, which is any score that
// is not a whole number of 5-point questions.
// AwardsPartialCredit(82) returns true. AwardsPartialCredit(90) returns false.
bool AwardsPartialCredit(int quiz_score);

// Returns whether a study plan is required. A plan is required unless the
// score has reached 70 and the review session was attended.
// RequiresStudyPlan(82, true) returns false.
// RequiresStudyPlan(82, false) returns true.
bool RequiresStudyPlan(int quiz_score, bool attended_review);

#endif