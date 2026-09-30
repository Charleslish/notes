#include "functions.hpp"

#include <fstream>
#include <string>
#include <vector>

struct Person {
  std::string name;
  std::vector<int> counts;
};

struct Database {
  std::vector<std::string> strs;
  std::vector<Person> people;
};

Database ReadDatabase(const std::string& filename) {
  Database database;
  std::ifstream ifs{filename};
  std::string line;
  std::getline(ifs, line);
  std::vector<std::string> columns = utilities::GetSubstrs(line, ',');
  for (size_t i = 1; i < columns.size(); ++i) 
    database.strs.push_back(columns[i]);

  while (std::getline(ifs, line)) {
    std::vector<std::string> row = utilities::GetSubstrs(line, ',');
    Person person;
    person.name = row[0];
    for (size_t i = 1; i < row.size(); ++i)
      person.counts.push_back(std::stoi(row[i]));
    database.people.push_back(person);
  }
  return database;
}

int LongestRun(const std::string& dna, const std::string& str) {
  int longest = 0;
  for (size_t i = 0; i < dna.size(); ) { 
    if (dna.substr(i, str.size()) == str) {
      int count = 0;
      size_t position = i;
      while (position + str.size() <= dna.size() && dna.substr(position, str.size()) == str) {
        ++count;
        position += str.size();
      }
      if (count > longest) 
        longest = count;
      i = position;
    } 
    else
      ++i;
  }
  return longest;
}

std::vector<int> GetSTRCounts(const std::string& dna, const std::vector<std::string>& strs) {
  std::vector<int> counts;
  for (const std::string& str : strs)
    counts.push_back(LongestRun(dna, str));
  return counts;
}

std::string ProfileDNA(const std::string& dna_database, const std::string& dna_sequence) {
  Database database = ReadDatabase(dna_database);
  std::vector<int> dna_counts = GetSTRCounts(dna_sequence, database.strs);
  std::vector<std::string> matching_people; 
  for (const Person& person : database.people) 
    if (person.counts == dna_counts) 
      matching_people.push_back(person.name);

  if (matching_people.size() == 1) 
    return matching_people[0];
  else 
    return "No match";
}