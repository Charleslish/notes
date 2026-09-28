#include "summary.hpp"

void AddAbove(double reading, double threshold, Summary& summary) {
  if (reading >= threshold) {
    summary.total_above += reading;
  }
}

void NoteSteady(double reading, double threshold, double limit,
                Summary& summary) {
  if (reading < threshold || reading > limit) {
    summary.steady = false;
    return;
  }
}

Summary Summarize(const std::vector<double>& readings, double threshold,
                  double limit) {
  Summary summary;
  unsigned int run = 0;
  for (unsigned int i = 0; i < readings.size(); ++i) {
    AddAbove(readings[i], threshold, summary);
    NoteSteady(readings[i], threshold, limit, summary);
    if (readings[i] >= threshold) {
      ++run;
      if (run > summary.longest_run) {
        summary.longest_run = run;
      }
    } else {
      run = 0;
    }
  }
  return summary;
}
