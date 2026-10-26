#ifndef VAULT_HPP
#define VAULT_HPP

#include <string>

struct Vault {
  std::string artifact;
  int next_vault = -1;
};

#endif
