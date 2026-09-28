
#include "solution.hpp"

std::map<std::string, std::vector<std::string>> SectionRosters(
    const std::vector<std::string>& signups,
    const std::map<std::string, std::string>& assigned) {
  std::map<std::string, std::vector<std::string>> rosters;
  for (const std::string& netid : signups) {
    if (assigned.contains(netid)) {
      std::string section = assigned.at(netid);
      rosters[section].push_back(netid);
    }
  }
  std::set<std::string> sections_to_remove;
  const int kMinimumRosterSize = 2;
  for (const auto& pair : rosters) {
    if (pair.second.size() < kMinimumRosterSize) {
      sections_to_remove.insert(pair.first);
    }
  }
  for (const std::string& section : sections_to_remove) {
    rosters.erase(section);
  }
  return rosters;
}