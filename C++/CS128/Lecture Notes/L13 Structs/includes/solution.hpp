#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

#include "reading.hpp"

unsigned int CountValid(const std::vector<Reading>& log);
Reading BestReading(const std::vector<Reading>& log);

#endif
