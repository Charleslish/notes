#ifndef BIKE_RACK_HPP
#define BIKE_RACK_HPP

class BikeRack {
 public:
  BikeRack(unsigned int size);
  BikeRack(const BikeRack& other) = delete;
  BikeRack& operator=(const BikeRack& other) = delete;
  ~BikeRack();
  unsigned int Size() const;
  bool Park(unsigned int slot, int bike);
  bool BikeAt(unsigned int slot, int& bike) const;
  bool Resize(unsigned int size);
  void TakeFrom(BikeRack& other);

 private:
  int* bikes_ = nullptr;
  unsigned int size_ = 0;
};

#endif
