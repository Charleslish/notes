#ifndef TABLE_HPP
#define TABLE_HPP

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

enum class DataType { kString, kDouble, kInt };

class DbTable {
 public:
  DbTable() = default;
  void AddColumn(const std::pair<std::string, DataType>& col_desc);
  void DeleteColumnByIdx(unsigned int col_idx);

  void AddRow(const std::initializer_list<std::string>& col_data);
  void DeleteRowById(unsigned int id);

  DbTable(const DbTable& rhs);
  DbTable& operator=(const DbTable& rhs);
  ~DbTable();

  friend std::ostream& operator<<(std::ostream& os, const DbTable& table);

 private:
  unsigned int next_unique_id_ = 0;
  unsigned int row_col_capacity_ = 2;
  std::map<unsigned int, void**> rows_;
  std::vector<std::pair<std::string, DataType>> col_descs_;
};

std::ostream& operator<<(std::ostream& os, const DbTable& table);

#endif
