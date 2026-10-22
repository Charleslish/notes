#include <iostream>
#include <string>

#include "artifact.hpp"
#include "vault.hpp"

int main() {
  Vault<Artifact> vault;
  std::cout << "Empty: " << vault.IsEmpty() << std::endl;

  vault.Store(Artifact("Ancient Map of the Northern Reach", 500));
  std::cout << "Empty: " << vault.IsEmpty() << std::endl;

  std::cout << "Peek: " << vault.Peek() << std::endl;
  std::cout << "Peek: " << vault.Peek() << std::endl;
  std::cout << "Access count: " << vault.GetAccessCount() << std::endl;

  Vault<std::string> string_vault;
  string_vault.Store("A secret message");
  std::cout << string_vault.Peek() << std::endl;

  Vault<int> int_vault;
  int_vault.Store(42);
  std::cout << int_vault.Peek() << std::endl;

  return 0;
}
