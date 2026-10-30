#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  DbTable table;
  table.AddColumn({"name", DataType::kString});
  table.AddColumn({"age", DataType::kInt});
  table.AddRow({"Ada", "20"});
  table.AddRow({"Grace", "21"});

  std::ostringstream table_output;
  table_output << table;
  assert(table_output.str() ==
         "name(std::string), age(int)\nAda, 20\nGrace, 21\n");

  table.AddColumn({"gpa", DataType::kDouble});
  std::ostringstream with_new_column;
  with_new_column << table;
  assert(with_new_column.str() ==
         "name(std::string), age(int), gpa(double)\nAda, 20, 0\nGrace, 21, 0\n");

  table.DeleteColumnByIdx(1);
  std::ostringstream after_delete_column;
  after_delete_column << table;
  assert(after_delete_column.str() ==
         "name(std::string), gpa(double)\nAda, 0\nGrace, 0\n");

  DbTable table_copy(table);
  table_copy.AddRow({"Linus", "3.5"});
  std::ostringstream original_after_copy_change;
  original_after_copy_change << table;
  assert(original_after_copy_change.str() == after_delete_column.str());

  table.DeleteRowById(0);
  table.AddRow({"Margaret", "4.0"});
  std::ostringstream after_delete_row;
  after_delete_row << table;
  assert(after_delete_row.str() ==
         "name(std::string), gpa(double)\nGrace, 0\nMargaret, 4\n");

  bool row_count_error = false;
  try {
    table.AddRow({"not enough values"});
  } catch (const std::invalid_argument&) {
    row_count_error = true;
  }
  assert(row_count_error);

  bool missing_row_error = false;
  try {
    table.DeleteRowById(0);
  } catch (const std::out_of_range&) {
    missing_row_error = true;
  }
  assert(missing_row_error);

  Database database;
  database.CreateTable("students");
  database.GetTable("students").AddColumn({"name", DataType::kString});
  database.GetTable("students").AddRow({"Ada"});

  Database database_copy(database);
  database_copy.GetTable("students").AddRow({"Grace"});
  std::ostringstream database_output;
  database_output << database;
  assert(database_output.str() == "students\nname(std::string)\nAda\n");

  database.DropTable("students");
  bool missing_table_error = false;
  try {
    database.GetTable("students");
  } catch (const std::out_of_range&) {
    missing_table_error = true;
  }
  assert(missing_table_error);

  std::cout << "All driver checks passed.\n";
}
