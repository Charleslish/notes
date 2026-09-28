#include "solution.hpp"

std::vector<std::vector<int>> ScoresByQuiz(const std::vector<std::vector<int>>& gradebook) {
  unsigned int max = 0;
  for (unsigned int row = 0; row < gradebook.size(); ++row) 
    max = (max > gradebook[row].size()) ? max : gradebook[row].size();
  std::vector<std::vector<int>> by_quiz(max);
  for (unsigned int row = 0; row < gradebook.size(); ++row) {
    for (unsigned int col = 0; col < gradebook[row].size(); ++col) {
      by_quiz[col].push_back(gradebook[row][col]);
    }
  }
  return by_quiz;
}
