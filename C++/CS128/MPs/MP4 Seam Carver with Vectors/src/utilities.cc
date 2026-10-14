#include "utilities.hpp"

#include <charconv>
#include <ostream>
#include <string>
#include <system_error>
#include <vector>

void Usage(std::ostream& output) {
  output << "Usage: bin/exec input.png [-v count] [-h count] -o output.png\n"
         << "Options are applied from left to right. Counts must be "
            "nonnegative.\n";
}

bool ParseCount(const std::string& text, unsigned int& count) {
  if (text.empty()) {
    return false;
  }
  const auto result =
      std::from_chars(text.data(), text.data() + text.size(), count);
  return result.ec == std::errc{} && result.ptr == text.data() + text.size();
}

bool ReadOptions(int argc, char** argv, std::vector<Operation>& operations,
                 std::string& output_path) {
  for (int index = 2; index < argc; index += 2) {
    if (index + 1 == argc) {
      return false;
    }
    const std::string option(argv[index]);
    if (option == "-o" && output_path.empty()) {
      output_path = argv[index + 1];
    } else if (option == "-h" || option == "-v") {
      unsigned int count = 0;
      if (!ParseCount(argv[index + 1], count)) {
        return false;
      }
      operations.push_back({option[1], count});
    } else {
      return false;
    }
  }
  return !output_path.empty();
}

bool CanApply(const Image& image, const std::vector<Operation>& operations) {
  unsigned int height = image.GetHeight();
  unsigned int width = image.GetWidth();
  for (const Operation& operation : operations) {
    unsigned int& dimension = operation.direction == 'v' ? width : height;
    if (operation.count >= dimension) {
      return false;
    }
    dimension -= operation.count;
  }
  return width > 0 && height > 0;
}

bool Apply(SeamCarver& carver, const std::vector<Operation>& operations) {
  for (const Operation& operation : operations) {
    for (unsigned int count = 0; count < operation.count; ++count) {
      const bool removed = operation.direction == 'v'
                               ? carver.RemoveVerticalSeam()
                               : carver.RemoveHorizontalSeam();
      if (!removed) {
        return false;
      }
    }
  }
  return true;
}
