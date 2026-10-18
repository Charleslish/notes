#ifndef VINEYARD_HPP
#define VINEYARD_HPP

class Vineyard {
 public:
  Vineyard(unsigned int rows, unsigned int vines);
  Vineyard(const Vineyard& other) = delete;
  Vineyard& operator=(const Vineyard& other) = delete;
  ~Vineyard();
  unsigned int Rows() const;
  unsigned int VinesPerRow() const;
  bool Record(unsigned int row, unsigned int vine, int grams);
  bool YieldAt(unsigned int row, unsigned int vine, int& grams) const;
  bool Resize(unsigned int rows, unsigned int vines);

 private:
  void DeleteRows();
  int** yields_ = nullptr;
  unsigned int rows_ = 0;
  unsigned int vines_ = 0;
};

#endif
