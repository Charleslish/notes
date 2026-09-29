#include "quest_log.hpp"

QuestLog::QuestLog(const std::string& hero) : hero_(hero) {}

QuestLog::QuestLog(const std::string& hero, int max_quests)
    : hero_(hero), max_quests_(max_quests) {
    if (max_quests_ < kMinMaxQuests)
        max_quests_ = kMinMaxQuests;
    else if (max_quests_ > kMaxMaxQuests)
        max_quests_ = kMaxMaxQuests;
} 

bool QuestLog::AddQuest(const std::string& name, Difficulty difficulty) {
    if (!CanAdd(name))
        return false;
    Quest quest {name, difficulty, false};
    quests_.push_back(quest);
    return true;
}

bool QuestLog::Complete(const std::string& name) {
    const size_t kIndex = FindQuest(name);
    if (kIndex == quests_.size() || quests_[kIndex].completed)
        return false;
    quests_[kIndex].completed = true;
    return true;
}

bool QuestLog::IsCompleted(const std::string& name) const {
    const size_t kIndex = FindQuest(name);
    if (kIndex == quests_.size())
        return false;
    return quests_[kIndex].completed;
}

int QuestLog::GetPoints() const {
    int points = 0;
    for (const Quest& quest : quests_) 
        if (quest.completed)
            points += PointsFor(quest.difficulty);
    return points;
}

unsigned int QuestLog::GetNumQuests() const {
    return quests_.size();
}

unsigned int QuestLog::GetNumCompleted() const {
    unsigned int count = 0;
    for (const Quest& quest : quests_) 
        if (quest.completed)
            ++count;
    return count;
}

std::string QuestLog::GetHero() const {
    return hero_;
}

int QuestLog::GetMaxQuests() const {
    return max_quests_;
}

bool QuestLog::CanAdd(const std::string& name) const {
    return !name.empty() && quests_.size() < static_cast<size_t>(max_quests_) && FindQuest(name) == quests_.size();
}

unsigned int QuestLog::FindQuest(const std::string& name) const {
    for (size_t i = 0; i < quests_.size(); ++i) 
        if (quests_[i].name == name) 
            return i;
    return quests_.size();
}

int QuestLog::PointsFor(Difficulty difficulty) const {
    if (difficulty == Difficulty::kEasy)
        return kEasyPoints;
    if (difficulty == Difficulty::kMedium)
        return kMediumPoints;
    return kHardPoints;
}

bool IsFinished(const QuestLog& log) {
    return log.GetNumQuests() != 0 && log.GetNumCompleted() == log.GetNumQuests();
}