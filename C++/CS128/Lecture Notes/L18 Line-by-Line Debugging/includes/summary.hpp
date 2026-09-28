#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <vector>

struct Summary {
  unsigned int longest_run{0};
  double total_above{0.0};
  bool steady{true};
};

void AddAbove(double reading, double threshold, Summary& summary);

void NoteSteady(double reading, double threshold, double limit, Summary& summary);

Summary Summarize(const std::vector<double>& readings, double threshold,
                  double limit);

#endif  // SUMMARY_HPP
