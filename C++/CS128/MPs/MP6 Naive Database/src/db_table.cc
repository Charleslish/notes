#include "db_table.hpp"

#include <stdexcept>

static void DeleteCell(void* cell, DataType type) {
  switch (type) {
    case DataType::kString:
      delete static_cast<std::string*>(cell);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(cell);
      break;
    case DataType::kInt:
      delete static_cast<int*>(cell);
      break;
  }
}

static void* CreateCell(const std::string& value, DataType type) {
  switch (type) {
    case DataType::kString:
      return static_cast<void*>(new std::string(value));
    case DataType::kDouble:
      return static_cast<void*>(new double(std::stod(value)));
    case DataType::kInt:
      return static_cast<void*>(new int(std::stoi(value)));
  }
  throw std::runtime_error("Invalid column data type");
}

static void* CreateZeroCell(DataType type) {
  switch (type) {
    case DataType::kString:
      return static_cast<void*>(new std::string());
    case DataType::kDouble:
      return static_cast<void*>(new double(0.0));
    case DataType::kInt:
      return static_cast<void*>(new int(0));
  }
  throw std::runtime_error("Invalid column data type");
}

static void* CloneCell(const void* cell, DataType type) {
  switch (type) {
    case DataType::kString:
      return static_cast<void*>(new std::string(*static_cast<const std::string*>(cell)));
    case DataType::kDouble:
      return static_cast<void*>(new double(*static_cast<const double*>(cell)));
    case DataType::kInt:
      return static_cast<void*>(new int(*static_cast<const int*>(cell)));
  }
  throw std::runtime_error("Invalid column data type");
}

static void DestroyRows(std::map<unsigned int, void**>& rows, const std::vector<std::pair<std::string, DataType>>& columns) {
  for (auto& [id, row] : rows) {
    static_cast<void>(id);
    for (unsigned int col = 0; col < columns.size(); ++col)
      DeleteCell(row[col], columns[col].second);
    delete[] row;
  }
  rows.clear();
}

static void WriteCell(std::ostream& os, const void* cell, DataType type) {
  switch (type) {
    case DataType::kString:
      os << *static_cast<const std::string*>(cell);
      break;
    case DataType::kDouble:
      os << *static_cast<const double*>(cell);
      break;
    case DataType::kInt:
      os << *static_cast<const int*>(cell);
      break;
  }
}

static const char* TypeName(DataType type) {
  switch (type) {
    case DataType::kString:
      return "std::string";
    case DataType::kDouble:
      return "double";
    case DataType::kInt:
      return "int";
  }
  return "unknown";
}

DbTable::DbTable(const DbTable& rhs): next_unique_id_(rhs.next_unique_id_), row_col_capacity_(rhs.row_col_capacity_), col_descs_(rhs.col_descs_) {
  try {
    for (const auto& [id, rhs_row] : rhs.rows_) {
      void** row = new void*[row_col_capacity_]{};
      try {
        for (unsigned int col = 0; col < col_descs_.size(); ++col)
          row[col] = CloneCell(rhs_row[col], col_descs_[col].second);
      } catch (...) {
        for (unsigned int col = 0; col < col_descs_.size(); ++col)
          if (row[col] != nullptr)
            DeleteCell(row[col], col_descs_[col].second);
        delete[] row;
        throw;
      }
      rows_.emplace(id, row);
    }
  } catch (...) {
    DestroyRows(rows_, col_descs_);
    throw;
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs)
    return *this;
  DbTable copy(rhs);
  DestroyRows(rows_, col_descs_);
  col_descs_.clear();
  col_descs_.insert(col_descs_.end(), copy.col_descs_.begin(), copy.col_descs_.end());
  next_unique_id_ = copy.next_unique_id_;
  row_col_capacity_ = copy.row_col_capacity_;
  rows_.swap(copy.rows_);
  return *this;
}

DbTable::~DbTable() { DestroyRows(rows_, col_descs_); }

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    const unsigned int new_capacity = row_col_capacity_ * 2;
    for (auto& [id, old_row] : rows_) {
      static_cast<void>(id);
      void** new_row = new void*[new_capacity]{};
      for (unsigned int col = 0; col < col_descs_.size(); ++col)
        new_row[col] = old_row[col];
      delete[] old_row;
      old_row = new_row;
    }
    row_col_capacity_ = new_capacity;
  }

  col_descs_.push_back(col_desc);
  for (auto& [id, row] : rows_) {
    static_cast<void>(id);
    row[col_descs_.size() - 1] = CreateZeroCell(col_desc.second);
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size())
    throw std::out_of_range("Column index is out of range");
  if (col_descs_.size() == 1 && !rows_.empty())
    throw std::runtime_error("Cannot delete the only column of a non-empty table");
  for (auto& [id, row] : rows_) {
    static_cast<void>(id);
    DeleteCell(row[col_idx], col_descs_[col_idx].second);
    for (unsigned int col = col_idx; col + 1 < col_descs_.size(); ++col)
      row[col] = row[col + 1];
    row[col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size())
    throw std::invalid_argument("Row data must match the number of columns");
  void** row = new void*[row_col_capacity_]{};
  auto value = col_data.begin();
  unsigned int col = 0;
  try {
    for (; col < col_descs_.size(); ++col, ++value)
      row[col] = CreateCell(*value, col_descs_[col].second);
    rows_.emplace(next_unique_id_, row);
  } catch (...) {
    for (unsigned int i = 0; i < col; ++i)
      DeleteCell(row[i], col_descs_[i].second);
    delete[] row;
    throw;
  }
  ++next_unique_id_;
}

void DbTable::DeleteRowById(unsigned int id) {
  const auto row_it = rows_.find(id);
  if (row_it == rows_.end())
    throw std::out_of_range("Row id does not exist");
  for (unsigned int col = 0; col < col_descs_.size(); ++col)
    DeleteCell(row_it->second[col], col_descs_[col].second);
  delete[] row_it->second;
  rows_.erase(row_it);
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int col = 0; col < table.col_descs_.size(); ++col) {
    if (col != 0)
      os << ", ";
    os << table.col_descs_[col].first << "(" << TypeName(table.col_descs_[col].second) << ")";
  }
  os << '\n';
  for (const auto& [id, row] : table.rows_) {
    static_cast<void>(id);
    for (unsigned int col = 0; col < table.col_descs_.size(); ++col) {
      if (col != 0)
        os << ", ";
      WriteCell(os, row[col], table.col_descs_[col].second);
    }
    os << '\n';
  }
  return os;
}