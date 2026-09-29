#include <iostream>

#include "quest_log.hpp"

int main() {
  const int kMaxQuests = 3;

  QuestLog log("Ayla", kMaxQuests);
  const bool added_dragon = log.AddQuest("Slay the dragon", Difficulty::kHard);
  const bool added_herbs = log.AddQuest("Gather herbs", Difficulty::kEasy);
  const bool added_again = log.AddQuest("Gather herbs", Difficulty::kMedium);
  const bool completed = log.Complete("Slay the dragon");

  std::cout << log.GetHero() << " holds " << log.GetNumQuests() << " of "
            << log.GetMaxQuests() << " quests" << std::endl;
  std::cout << "added: " << added_dragon << added_herbs << added_again
            << ", completed: " << completed << std::endl;
  std::cout << "dragon completed: " << log.IsCompleted("Slay the dragon")
            << ", herbs completed: " << log.IsCompleted("Gather herbs")
            << std::endl;
  std::cout << "points: " << log.GetPoints() << ", finished: "
            << IsFinished(log) << std::endl;

  const QuestLog kNewcomer;
  std::cout << kNewcomer.GetHero() << " holds up to "
            << kNewcomer.GetMaxQuests() << " quests" << std::endl;
  return 0;
}
