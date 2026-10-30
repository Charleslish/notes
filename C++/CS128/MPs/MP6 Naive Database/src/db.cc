#include "db.hpp"

#include <stdexcept>

Database::Database(const Database& rhs) {
  try {
    for (const auto& [name, table] : rhs.tables_)
      tables_.emplace(name, new DbTable(*table));
  } catch (...) {
    for (auto& [name, table] : tables_) {
      static_cast<void>(name);
      delete table;
    }
    tables_.clear();
    throw;
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this == &rhs)
    return *this;

  Database copy(rhs);
  for (auto& [name, table] : tables_) {
    static_cast<void>(name);
    delete table;
  }
  tables_.clear();
  tables_.swap(copy.tables_);
  return *this;
}

Database::~Database() {
  for (auto& [name, table] : tables_) {
    static_cast<void>(name);
    delete table;
  }
  tables_.clear();
}

void Database::CreateTable(const std::string& table_name) {
  if (tables_.contains(table_name))
    throw std::runtime_error("already exists");
  tables_.emplace(table_name, new DbTable());
}

void Database::DropTable(const std::string& table_name) {
  const auto table_it = tables_.find(table_name);
  if (table_it == tables_.end())
    throw std::out_of_range("does not exist");
  delete table_it->second;
  tables_.erase(table_it);
}

DbTable& Database::GetTable(const std::string& table_name) {
  const auto table_it = tables_.find(table_name);
  if (table_it == tables_.end())
    throw std::out_of_range("does not exist");
  return *table_it->second;
}

std::ostream& operator<<(std::ostream& os, const Database& database) {
  for (const auto& [name, table] : database.tables_)
    os << name << '\n' << *table;
  return os;
}
