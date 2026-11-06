#include <iostream>
#include <string>
#include <vector>

#include "forest_trail.hpp"
#include "follow_trail.hpp"

int main() {
  ForestTrail trail;
  trail.AddLandmark("Maple Ridge");
  trail.AddLandmark("Birch Bridge");
  trail.AddLandmark("Pine Summit");
  trail.AddLandmark("Aspen Grove");
  trail.AddLandmark("Cedar Falls");
  trail.AddLandmark("Oak Clearing");
  trail.AddLandmark("Willow Bend");

  std::vector<std::string> route1 = {
      "Maple Ridge", "Pine Summit"};

  std::vector<std::string> result1 = FollowTrail(trail.start(), route1);

  std::cout << "Route to Pine Summit:" << std::endl;
  for (const std::string& landmark : result1) {
    std::cout << "  -> " << landmark << std::endl;
  }

  std::cout << std::endl;

  std::vector<std::string> route2 = {
      "Maple Ridge", "Birch Bridge", "Aspen Grove"};

  std::vector<std::string> result2 = FollowTrail(trail.start(), route2);

  std::cout << "Route to Aspen Grove:" << std::endl;
  for (const std::string& landmark : result2) {
    std::cout << "  -> " << landmark << std::endl;
  }

  std::cout << std::endl;

  std::vector<std::string> route3 = {
      "Maple Ridge", "Pine Summit", "Willow Bend"};

  std::vector<std::string> result3 = FollowTrail(trail.start(), route3);

  std::cout << "Route to Willow Bend:" << std::endl;
  for (const std::string& landmark : result3) {
    std::cout << "  -> " << landmark << std::endl;
  }

  return 0;
}
