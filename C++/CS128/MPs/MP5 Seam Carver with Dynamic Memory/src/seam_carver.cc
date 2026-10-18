#include "seam_carver.hpp"

SeamCarver::SeamCarver() : image_(new Image()) {}

SeamCarver::SeamCarver(const Image& image): image_(new Image(image)) {}

SeamCarver::SeamCarver(const SeamCarver& other): image_(new Image(*other.image_)) {}

SeamCarver& SeamCarver::operator=(const SeamCarver& other) {
  if (this != &other)
    *image_ = *other.image_;
  return *this;
}

SeamCarver::~SeamCarver() { delete image_; }

void SeamCarver::SetImage(const Image& image) { *image_ = image; }

const Image& SeamCarver::GetImage() const { return *image_; }

unsigned int SeamCarver::GetHeight() const { return image_->GetHeight(); }

unsigned int SeamCarver::GetWidth() const { return image_->GetWidth(); }

int SeamCarver::GetEnergy(unsigned int row, unsigned int col) const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  const unsigned int left_col = (col == 0) ? width - 1 : col - 1;
  const unsigned int right_col = (col + 1 == width) ? 0 : col + 1;
  const unsigned int above_row = (row == 0) ? height - 1 : row - 1;
  const unsigned int below_row = (row + 1 == height) ? 0 : row + 1;
  const Pixel left = image_->GetPixel(row, left_col);
  const Pixel right = image_->GetPixel(row, right_col);
  const Pixel above = image_->GetPixel(above_row, col);
  const Pixel below = image_->GetPixel(below_row, col);
  const int red_lr = left.GetRed() - right.GetRed();
  const int green_lr = left.GetGreen() - right.GetGreen();
  const int blue_lr = left.GetBlue() - right.GetBlue();
  const int red_ud = above.GetRed() - below.GetRed();
  const int green_ud = above.GetGreen() - below.GetGreen();
  const int blue_ud = above.GetBlue() - below.GetBlue();
  return red_lr * red_lr + green_lr * green_lr + blue_lr * blue_lr + red_ud * red_ud + green_ud * green_ud + blue_ud * blue_ud;
}

int** SeamCarver::BuildEnergyTable() const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height == 0)
    return nullptr;
  int** energies = new int*[height];
  for (unsigned int row = 0; row < height; ++row) {
    energies[row] = new int[width];
    for (unsigned int col = 0; col < width; ++col)
      energies[row][col] = GetEnergy(row, col);
  }
  return energies;
}

int** SeamCarver::AccumulateVerticalCosts(const int* const* energies) const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height == 0) 
    return nullptr;
  int** costs = new int*[height];
  for (unsigned int row = 0; row < height; ++row) {
    costs[row] = new int[width];
    for (unsigned int col = 0; col < width; ++col)
      costs[row][col] = energies[row][col];
  }
  for (unsigned int row = height - 1; row > 0; --row) {
    for (unsigned int col = 0; col < width; ++col) {
      int best = costs[row][col];
      if (col > 0 && costs[row][col - 1] < best)
        best = costs[row][col - 1];
      if (col + 1 < width && costs[row][col + 1] < best)
        best = costs[row][col + 1];
      costs[row - 1][col] += best;
    }
  }
  return costs;
}

int** SeamCarver::AccumulateHorizontalCosts(const int* const* energies) const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height == 0)
    return nullptr;
  int** costs = new int*[height];
  for (unsigned int row = 0; row < height; ++row) {
    costs[row] = new int[width];
    for (unsigned int col = 0; col < width; ++col)
      costs[row][col] = energies[row][col];
  }
  for (unsigned int col = width - 1; col > 0; --col) {
    for (unsigned int row = 0; row < height; ++row) {
      int best = costs[row][col];
      if (row > 0 && costs[row - 1][col] < best)
        best = costs[row - 1][col];
      if (row + 1 < height && costs[row + 1][col] < best)
        best = costs[row + 1][col];
      costs[row][col - 1] += best;
    }
  }
  return costs;
}

unsigned int* SeamCarver::TraceVerticalSeam(const int* const* costs) const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height == 0)
    return nullptr;
  unsigned int* seam = new unsigned int[height];
  seam[0] = 0;
  for (unsigned int col = 1; col < width; ++col)
    if (costs[0][col] < costs[0][seam[0]])
      seam[0] = col;
  for (unsigned int row = 1; row < height; ++row) {
    const unsigned int prev = seam[row - 1];
    unsigned int best_col = prev;
    if (prev > 0 && costs[row][prev - 1] < costs[row][best_col])
      best_col = prev - 1;
    if (prev + 1 < width && costs[row][prev + 1] < costs[row][best_col])
      best_col = prev + 1;
    seam[row] = best_col;
  }
  return seam;
}

unsigned int* SeamCarver::TraceHorizontalSeam(const int* const* costs) const {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height == 0)
    return nullptr;
  unsigned int* seam = new unsigned int[width];
  seam[0] = 0;
  for (unsigned int row = 1; row < height; ++row) 
    if (costs[row][0] < costs[seam[0]][0]) 
      seam[0] = row;
  for (unsigned int col = 1; col < width; ++col) {
    const unsigned int prev = seam[col - 1];
    unsigned int best_row = prev;
    if (prev > 0 && costs[prev - 1][col] < costs[best_row][col])
      best_row = prev - 1;
    if (prev + 1 < height && costs[prev + 1][col] < costs[best_row][col])
      best_row = prev + 1;
    seam[col] = best_row;
  }
  return seam;
}

unsigned int* SeamCarver::GetVerticalSeam() const {
  int** energies = BuildEnergyTable();
  if (GetHeight() == 0)
    return nullptr;
  int** costs = AccumulateVerticalCosts(energies);
  unsigned int* seam = TraceVerticalSeam(const_cast<const int* const*>(costs));
  for (unsigned int row = 0; row < GetHeight(); ++row) {
    delete[] energies[row];
    delete[] costs[row];
  }
  delete[] energies;
  delete[] costs;
  return seam;
}

unsigned int* SeamCarver::GetHorizontalSeam() const {
  int** energies = BuildEnergyTable();
  if (GetHeight() == 0) 
    return nullptr;
  int** costs = AccumulateHorizontalCosts(energies);
  unsigned int* seam = TraceHorizontalSeam(const_cast<const int* const*>(costs));
  for (unsigned int row = 0; row < GetHeight(); ++row) {
    delete[] energies[row];
    delete[] costs[row];
  }
  delete[] energies;
  delete[] costs;
  return seam;
}

bool SeamCarver::RemoveVerticalSeam() {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (width <= 1) 
    return false;
  unsigned int* seam = GetVerticalSeam();
  for (unsigned int row = 0; row < height; ++row) 
    for (unsigned int col = seam[row]; col + 1 < width; ++col)
      image_->SetPixel(row, col, image_->GetPixel(row, col + 1));
  delete[] seam;
  image_->Crop(height, width - 1);
  return true;
}

bool SeamCarver::RemoveHorizontalSeam() {
  const unsigned int height = GetHeight();
  const unsigned int width = GetWidth();
  if (height <= 1) 
    return false;
  unsigned int* seam = GetHorizontalSeam();
  for (unsigned int col = 0; col < width; ++col) 
    for (unsigned int row = seam[col]; row + 1 < height; ++row) 
      image_->SetPixel(row, col, image_->GetPixel(row + 1, col));
  delete[] seam;
  image_->Crop(height - 1, width);
  return true;
}