#include "solution.hpp"

std::vector<std::string> UsedOnce(const std::vector<std::string>& draft) {
  std::vector<std::string> listed;
  std::set<std::string> appeared;
  std::set<std::string> repeated;
  for(unsigned int i = 0; i < draft.size(); ++i){
    if(!appeared.contains(draft[i])&&!repeated.contains(draft[i]))
      appeared.insert(draft[i]);
    else
    {
      appeared.erase(draft[i]);
      repeated.insert(draft[i]);
    }
  }
  for(const auto& i : appeared){
    listed.push_back(i);
  }
  return listed;
}
