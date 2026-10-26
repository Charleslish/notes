#include "exhibit_catalog.hpp"

ExhibitCatalog::ExhibitCatalog(int initial_capacity) : capacity_(initial_capacity) {
  vaults_ = new Vault[capacity_];
  for (int index = 0; index < capacity_; ++index) {
    available_.insert(index);
  }
}

ExhibitCatalog::~ExhibitCatalog() { delete[] vaults_; }

void ExhibitCatalog::AddToFront(const std::string& artifact) {
  if (available_.empty()) Resize();
  const int kSlot = *available_.begin();
  available_.erase(available_.begin());
  vaults_[kSlot].artifact = artifact;
  vaults_[kSlot].next_vault = head_;
  head_ = kSlot;
  ++size_;
}

void ExhibitCatalog::AddAfter(int vault_index, const std::string& artifact) {
  if (available_.empty()) Resize();
  const int kSlot = *available_.begin();
  available_.erase(available_.begin());
  vaults_[kSlot].artifact = artifact;
  vaults_[kSlot].next_vault = vaults_[vault_index].next_vault;
  vaults_[vault_index].next_vault = kSlot;
  ++size_;
}

void ExhibitCatalog::Remove(int vault_index) {
  if (head_ == vault_index) {
    head_ = vaults_[vault_index].next_vault;
  } else {
    int previous = head_;
    while (vaults_[previous].next_vault != vault_index) {
      previous = vaults_[previous].next_vault;
    }
    vaults_[previous].next_vault = vaults_[vault_index].next_vault;
  }
  vaults_[vault_index].artifact.clear();
  vaults_[vault_index].next_vault = -1;
  available_.insert(vault_index);
  --size_;
}

std::vector<std::string> ExhibitCatalog::GetTourOrder() const {
  std::vector<std::string> order;
  int current = head_;
  while (current != -1) {
    order.push_back(vaults_[current].artifact);
    current = vaults_[current].next_vault;
  }
  return order;
}

void ExhibitCatalog::Resize() {
  const int kNewCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
  Vault* expanded = new Vault[kNewCapacity];
  for (int index = 0; index < capacity_; ++index) {
    expanded[index] = vaults_[index];
  }
  delete[] vaults_;
  vaults_ = expanded;
  for (int index = capacity_; index < kNewCapacity; ++index) {
    available_.insert(index);
  }
  capacity_ = kNewCapacity;
}

int ExhibitCatalog::GetSize() const { return size_; }
int ExhibitCatalog::GetCapacity() const { return capacity_; }
int ExhibitCatalog::GetHead() const { return head_; }
