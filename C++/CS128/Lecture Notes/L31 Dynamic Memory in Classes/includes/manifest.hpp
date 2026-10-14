#ifndef MANIFEST_HPP
#define MANIFEST_HPP

class Manifest {
 public:
  Manifest(unsigned int size);
  Manifest(const Manifest& other);
  Manifest& operator=(const Manifest& other);
  ~Manifest();
  unsigned int Size() const;
  bool Load(unsigned int slot, int vehicle);
  bool VehicleAt(unsigned int slot, int& vehicle) const;

 private:
  int* vehicles_ = nullptr;
  unsigned int size_ = 0;
};

#endif
