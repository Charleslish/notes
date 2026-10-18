#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <ostream>
#include <string>
#include <vector>

#include "image.hpp"
#include "seam_carver.hpp"

struct Operation {
  char direction;
  unsigned int count;
};

void Usage(std::ostream& output);
bool ParseCount(const std::string& text, unsigned int& count);
bool ReadOptions(int argc, char** argv, std::vector<Operation>& operations,
                 std::string& output_path);
bool CanApply(const Image& image, const std::vector<Operation>& operations);
bool Apply(SeamCarver& carver, const std::vector<Operation>& operations);

#endif
