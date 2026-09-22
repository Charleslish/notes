#include <iostream>
#include <vector>

#include "reading.hpp"
#include "solution.hpp"

int main() {
  std::vector<Reading> log{{301, 21, true}, {302, 30, false}, {303, 25, true}};

  std::cout << "valid readings: " << CountValid(log) << std::endl;

  Reading best = BestReading(log);
  std::cout << "best: sensor " << best.sensor_id << ", " << best.celsius
            << " C, valid " << best.is_valid << std::endl;

  return 0;
}
