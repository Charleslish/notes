#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP

#include <iostream>
#include <string>

class Artifact {
 public:
  Artifact() = default;
  Artifact(const std::string& name, int age);

  std::string GetName() const;
  int GetAge() const;

  friend std::ostream& operator<<(std::ostream& os, const Artifact& a);

 private:
  std::string name_;
  int age_ = 0;
};

#endif
