#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "solution.hpp"

int main() {
  std::vector<std::string> signups {"ada", "grace", "mary"};
  std::map<std::string, std::string> assigned {
      {"ada", "DIS1"}, {"grace", "DIS1"}, {"mary", "DIS2"}};
  std::map<std::string, std::vector<std::string>> rosters = SectionRosters(signups, assigned);
  std::cout << "sections that run: " << rosters.size() << std::endl;
  for (const auto& [section, roster] : rosters) {
    std::cout << section << ":";
    for (unsigned int i = 0; i < roster.size(); ++i) {
      std::cout << " " << roster[i];
    }
    std::cout << std::endl;
  }
  return 0;
}
