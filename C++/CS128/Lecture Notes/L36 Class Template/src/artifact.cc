#include "artifact.hpp"

Artifact::Artifact(const std::string& name, int age)
    : name_(name), age_(age) {}

std::string Artifact::GetName() const { return name_; }

int Artifact::GetAge() const { return age_; }

std::ostream& operator<<(std::ostream& os, const Artifact& a) {
  os << a.name_ << " (" << a.age_ << " years old)";
  return os;
}
