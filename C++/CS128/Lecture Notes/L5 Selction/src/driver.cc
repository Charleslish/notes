#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kQuizScore = 82;
  constexpr bool kAttendedReview = true;

  std::cout << "band: " << QuizBand(kQuizScore) << std::endl;
  std::cout << "partial credit: " << AwardsPartialCredit(kQuizScore)
            << std::endl;
  std::cout << "study plan required: "
            << RequiresStudyPlan(kQuizScore, kAttendedReview) << std::endl;

  return 0;
}
