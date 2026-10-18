#ifndef SEAM_CARVER_HPP
#define SEAM_CARVER_HPP

#include "image.hpp"

class SeamCarver {
 public:
  SeamCarver();
  SeamCarver(const SeamCarver& other);
  SeamCarver& operator=(const SeamCarver& other);
  ~SeamCarver();
  explicit SeamCarver(const Image& image);
  void SetImage(const Image& image);
  const Image& GetImage() const;
  unsigned int GetHeight() const;
  unsigned int GetWidth() const;
  int GetEnergy(unsigned int row, unsigned int col) const;
  unsigned int* GetVerticalSeam() const;
  unsigned int* GetHorizontalSeam() const;
  bool RemoveVerticalSeam();
  bool RemoveHorizontalSeam();

 private:
  Image* image_ = nullptr;
  int** BuildEnergyTable() const;
  int** AccumulateVerticalCosts(const int* const* energies) const;
  int** AccumulateHorizontalCosts(const int* const* energies) const;
  unsigned int* TraceVerticalSeam(const int* const* costs) const;
  unsigned int* TraceHorizontalSeam(const int* const* costs) const;
};

#endif
