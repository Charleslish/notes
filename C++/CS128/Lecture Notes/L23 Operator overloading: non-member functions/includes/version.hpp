#ifndef VERSION_HPP
#define VERSION_HPP

#include <ostream>

class Version {
 public:
  Version(int major, int minor, int patch);

  int GetMajor() const;
  int GetMinor() const;
  int GetPatch() const;

 private:
  static constexpr int kMinComponent = 0;

  int major_ = kMinComponent;
  int minor_ = kMinComponent;
  int patch_ = kMinComponent;
};

bool operator==(const Version& lhs, const Version& rhs);
bool operator<(const Version& lhs, const Version& rhs);
std::ostream& operator<<(std::ostream& os, const Version& version);

#endif
