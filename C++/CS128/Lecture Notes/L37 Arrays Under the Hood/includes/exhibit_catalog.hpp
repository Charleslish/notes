#ifndef EXHIBIT_CATALOG_HPP
#define EXHIBIT_CATALOG_HPP

#include <set>
#include <string>
#include <vector>

#include "vault.hpp"

class ExhibitCatalog {
 public:
  ExhibitCatalog(int initial_capacity);
  ~ExhibitCatalog();

  ExhibitCatalog(const ExhibitCatalog& other) = delete;
  ExhibitCatalog& operator=(const ExhibitCatalog& other) = delete;

  void AddToFront(const std::string& artifact);
  void AddAfter(int vault_index, const std::string& artifact);
  void Remove(int vault_index);
  std::vector<std::string> GetTourOrder() const;
  void Resize();

  int GetSize() const;
  int GetCapacity() const;
  int GetHead() const;

 private:
  Vault* vaults_ = nullptr;
  int capacity_ = 0;
  int size_ = 0;
  int head_ = -1;
  std::set<int> available_;
};

#endif
