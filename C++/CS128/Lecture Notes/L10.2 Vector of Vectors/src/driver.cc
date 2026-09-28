#include <iostream>

#include "solution.hpp"

int main() {
  std::vector<std::vector<int>> gradebook {{77, 92, 68}, {83, 71}, {90, 64, 88, 75}};
  std::vector<std::vector<int>> by_quiz = ScoresByQuiz(gradebook);
  std::cout << "quizzes: " << by_quiz.size() << std::endl;
  for (unsigned int quiz = 0; quiz < by_quiz.size(); ++quiz) {
    std::cout << "quiz " << quiz << ":";
    for (unsigned int student = 0; student < by_quiz[quiz].size(); ++student) {
      std::cout << " " << by_quiz[quiz][student];
    }
    std::cout << std::endl;
  }
  return 0;
}
