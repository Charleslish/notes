#include <iostream>

#include "version.hpp"

int main() {
  const Version kInstalled(1, 9, 3);
  const Version kRelease(1, 10, 0);
  const Version kSameRelease(1, 10, 0);
  const Version kLimited(-2, 4, -7);

  std::cout << "installed: " << kInstalled << std::endl;
  std::cout << "release: " << kRelease << std::endl;
  std::cout << "limited: " << kLimited << std::endl;
  std::cout << "installed == release: " << (kInstalled == kRelease) << std::endl;
  std::cout << "release == same release: " << (kRelease == kSameRelease)
            << std::endl;
  std::cout << "installed != release: " << (kInstalled != kRelease) << std::endl;
  std::cout << "installed < release: " << (kInstalled < kRelease) << std::endl;
  std::cout << "release < installed: " << (kRelease < kInstalled) << std::endl;
  return 0;
}
