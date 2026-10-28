#include "scavenger.hpp"

#include <iostream>
#include <string>

int main() {
  FirstClue* clue = new FirstClue{"opensesame", 42};
  Prize result = SolveScavengerHunt(clue);
  std::cout << result.message << std::endl;
  delete clue;

  FirstClue* clue2 = new FirstClue{"hello", 7};
  Prize result2 = SolveScavengerHunt(clue2);
  std::cout << result2.message << std::endl;
  delete clue2;

  return 0;
}
