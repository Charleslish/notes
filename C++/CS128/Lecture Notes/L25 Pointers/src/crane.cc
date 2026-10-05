#include "crane.hpp"

Crane::Crane(unsigned int max_tonnes) : max_tonnes_(max_tonnes) {}
bool Crane::Lift(Container* container) {
  if (hook_ != nullptr || !CanLift(container))
    return false;
  hook_ = container;
  return true;
}
Container* Crane::Release() {
  Container* const kReleased = hook_;
  hook_ = nullptr;
  return kReleased;
}
bool Crane::Stow() {
  if (hook_ == nullptr)
    return false;
  hook_->is_stowed = true;
  hook_ = nullptr;
  return true;
}
bool Crane::HandOff(Crane* other){
    if (other == nullptr || hook_ == nullptr || other->hook_ != nullptr || !other->CanLift(hook_))
        return false;
    other->hook_ = hook_;
    hook_ = nullptr;
    return true;
}
bool Crane::IsHolding(const Container* container) const {
    return hook_ == container;
}
const Container* Crane::Holding() const {
    return hook_;
}
Container* Crane::HeaviestLiftable(std::vector<Container>& yard) const{
    Container* heaviest = nullptr;
    for (Container& container : yard) 
        if (!container.is_stowed && CanLift(&container) && hook_ != &container)
            if (heaviest == nullptr || container.tonnes > heaviest->tonnes) 
                heaviest = &container;
    return heaviest;
}
unsigned int Crane::GetMaxTonnes() const {
    return max_tonnes_;
}
bool Crane::CanLift(const Container* container) const {
    return container != nullptr && !container->is_stowed && container->tonnes <= max_tonnes_;
}
