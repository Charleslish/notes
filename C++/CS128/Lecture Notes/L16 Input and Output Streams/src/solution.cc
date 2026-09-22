#include "solution.hpp"

std::vector<int> ReadReadings(std::istream& in) {
    std::vector<int> readings;
    while (in.good()) {
        int value = 0;
        in >> value;
        if (in.bad())
            break;
        if (in.fail()) {
            if (in.eof()) 
                break;
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        readings.push_back(value);
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  return readings;
}
