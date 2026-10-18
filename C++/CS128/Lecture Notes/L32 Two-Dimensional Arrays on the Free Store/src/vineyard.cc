#include "vineyard.hpp"

Vineyard::Vineyard(unsigned int rows, unsigned int vines): rows_(rows), vines_(vines) {
  if (rows_ == 0 || vines_ == 0) {
    rows_ = 0;
    vines_ = 0;
    return;
  }
  yields_ = new int*[rows_]{};
  for (unsigned int row = 0; row < rows_; ++row) 
    yields_[row] = new int[vines_]{};
}

Vineyard::~Vineyard() { DeleteRows(); }
unsigned int Vineyard::Rows() const { return rows_; }
unsigned int Vineyard::VinesPerRow() const { return vines_; }
bool Vineyard::Record(unsigned int row, unsigned int vine, int grams) {
  if (row >= rows_ || vine >= vines_)
    return false;
  yields_[row][vine] = grams;
  return true;
}

bool Vineyard::YieldAt(unsigned int row, unsigned int vine, int& grams) const {
  if (row >= rows_ || vine >= vines_)
    return false;
  grams = yields_[row][vine];
  return true;
}

bool Vineyard::Resize(unsigned int rows, unsigned int vines) {
  if (rows == 0 || vines == 0)
    return false;
  int** resized = new int*[rows]{};
  for (unsigned int row = 0; row < rows; ++row)
    resized[row] = new int[vines]{};
  for (unsigned int row = 0; row < rows_ && row < rows; ++row) 
    for (unsigned int vine = 0; vine < vines_ && vine < vines; ++vine) 
      resized[row][vine] = yields_[row][vine];
  DeleteRows();
  yields_ = resized;
  rows_ = rows;
  vines_ = vines;
  return true;
}

void Vineyard::DeleteRows() {
  for (unsigned int row = 0; row < rows_; ++row) 
    delete[] yields_[row];
  delete[] yields_;
  yields_ = nullptr;
  rows_ = 0;
  vines_ = 0;
}