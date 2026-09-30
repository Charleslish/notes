#include <iostream>
#include <string>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) return 1;
  // (0) cultivate arguments, open dna database
  const std::string kDatabaseDNA = argv[1];
  const std::string kSequenceDNA = argv[2];
  std::cout << ProfileDNA(kDatabaseDNA, kSequenceDNA);
}