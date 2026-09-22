#include "solution.hpp"

char QuizBand(int quiz_score) {
  // TODO: Return the band the score falls in, using an if / else if / else
  // chain over named constants.
  const int kHscore = 90;
  const int kPscore = 70;
  const int kCscore = 50;
  if (quiz_score >= kHscore)
    return 'h';
  else if (quiz_score >= kPscore)
    return 'p';
  else if (quiz_score >= kCscore)
    return 'c';
  return 'a';
}

bool AwardsPartialCredit(int quiz_score) {
  // TODO: Return whether the score is not a whole number of 5-point
  // questions. Name the points-per-question as a constant; a bare 5
  // fails the clear-code checks.
  const int kPointsPerQuestion = 5;
  return (quiz_score % kPointsPerQuestion != 0);
}

bool RequiresStudyPlan(int quiz_score, bool attended_review) {
  // TODO: Return whether a study plan is required.
  const int kPscore = 70;
  return (quiz_score < kPscore || !attended_review);
}
