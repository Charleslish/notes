#include <iostream>
#include <string>
#include <vector>

#include "image.hpp"
#include "png_io.hpp"
#include "seam_carver.hpp"
#include "utilities.hpp"

int main(int argc, char** argv) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    Usage(std::cout);
    return 0;
  }
  std::vector<Operation> operations;
  std::string output_path;
  if (argc < 4 || !ReadOptions(argc, argv, operations, output_path)) {
    Usage(std::cerr);
    return 1;
  }
  Image image;
  if (!ReadPng(argv[1], &image)) {
    std::cerr << "Could not read a supported RGB PNG: " << argv[1] << '\n';
    return 1;
  }
  if (!CanApply(image, operations)) {
    std::cerr
        << "The requested removals would leave no pixels in a row or column.\n";
    return 1;
  }
  SeamCarver carver(image);
  if (!Apply(carver, operations)) {
    std::cerr << "A seam removal failed. No output was written.\n";
    return 1;
  }
  if (!WritePng(output_path, carver.GetImage())) {
    std::cerr << "Could not write output PNG: " << output_path << '\n';
    return 1;
  }
  std::cout << "Wrote " << output_path << " (" << carver.GetWidth() << " x "
            << carver.GetHeight() << ")\n";
}
