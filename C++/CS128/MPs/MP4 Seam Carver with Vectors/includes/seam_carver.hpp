#ifndef SEAM_CARVER_HPP
#define SEAM_CARVER_HPP

#include <vector>

#include "image.hpp"

class SeamCarver {
 public:
  SeamCarver() = default;
  explicit SeamCarver(const Image& image);
  void SetImage(const Image& image);
  const Image& GetImage() const;
  unsigned int GetHeight() const;
  unsigned int GetWidth() const;
  int GetEnergy(unsigned int row, unsigned int col) const;
  std::vector<unsigned int> GetVerticalSeam() const;
  std::vector<unsigned int> GetHorizontalSeam() const;
  bool RemoveVerticalSeam();
  bool RemoveHorizontalSeam();

 private:
  Image image_;
  std::vector<std::vector<int>> BuildEnergyTable() const;
  std::vector<std::vector<int>> AccumulateVerticalCosts(
      const std::vector<std::vector<int>>& energies) const;
  std::vector<std::vector<int>> AccumulateHorizontalCosts(
      const std::vector<std::vector<int>>& energies) const;
  std::vector<unsigned int> TraceVerticalSeam(
      const std::vector<std::vector<int>>& costs) const;
  std::vector<unsigned int> TraceHorizontalSeam(
      const std::vector<std::vector<int>>& costs) const;
};

#endif
