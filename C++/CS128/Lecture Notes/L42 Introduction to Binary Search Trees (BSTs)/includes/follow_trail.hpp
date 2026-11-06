#ifndef FOLLOW_TRAIL_HPP
#define FOLLOW_TRAIL_HPP

#include <string>
#include <vector>

#include "path_node.hpp"

std::vector<std::string> FollowTrail(const PathNode* start,
                                     const std::vector<std::string>& route);

#endif
