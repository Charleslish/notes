#ifndef QUEST_LOG_HPP
#define QUEST_LOG_HPP

#include <string>
#include <vector>

enum class Difficulty { kEasy, kMedium, kHard };

struct Quest {
  std::string name;
  Difficulty difficulty = Difficulty::kEasy;
  bool completed = false;
};

class QuestLog {
 public:
  QuestLog() = default;
  explicit QuestLog(const std::string& hero);
  QuestLog(const std::string& hero, int max_quests);
  bool AddQuest(const std::string& name, Difficulty difficulty);
  bool Complete(const std::string& name);
  bool IsCompleted(const std::string& name) const;
  int GetPoints() const;
  unsigned int GetNumQuests() const;
  unsigned int GetNumCompleted() const;
  std::string GetHero() const;
  int GetMaxQuests() const;

 private:
  static constexpr int kMinMaxQuests = 1;
  static constexpr int kMaxMaxQuests = 10;
  static constexpr int kEasyPoints = 10;
  static constexpr int kMediumPoints = 25;
  static constexpr int kHardPoints = 50;
  bool CanAdd(const std::string& name) const;
  unsigned int FindQuest(const std::string& name) const;
  int PointsFor(Difficulty difficulty) const;
  std::string hero_ = "Adventurer";
  int max_quests_ = kMaxMaxQuests;
  std::vector<Quest> quests_;
};

bool IsFinished(const QuestLog& log);

#endif
