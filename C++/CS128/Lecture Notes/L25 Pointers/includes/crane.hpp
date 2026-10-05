#ifndef CRANE_HPP
#define CRANE_HPP

#include <string>
#include <vector>

struct Container {
  std::string code;
  unsigned int tonnes = 0;
  bool is_stowed = false;
};

class Crane {
 public:
  Crane() = default;
  explicit Crane(unsigned int max_tonnes);
  bool Lift(Container* container);
  Container* Release();
  bool Stow();
  bool HandOff(Crane* other);
  bool IsHolding(const Container* container) const;
  const Container* Holding() const;
  Container* HeaviestLiftable(std::vector<Container>& yard) const;
  unsigned int GetMaxTonnes() const;

 private:
  static constexpr unsigned int kDefaultMaxTonnes = 30;
  bool CanLift(const Container* container) const;
  Container* hook_ = nullptr;
  unsigned int max_tonnes_ = kDefaultMaxTonnes;
};

#endif
