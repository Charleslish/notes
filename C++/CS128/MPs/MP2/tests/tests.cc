#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <string>

#include "catch.hpp"
#include "functions.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// Written By : Michael R. Nowak
// Date ......: 2023/05/29
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "functions.hpp"

TEST_CASE("test-strs-1-test-1", "[test-strs-1-test-1]") {
  std::string dna_database = "./tests/dna_databases/test-strs-1.dat";
  std::string dna_sequence =
      "AGACGGGTTACCATGACTATCTATCTATCTATCTATCTATCTATCTATCACGTACGTACGTATCGAGATAGA"
      "TAGATAGATAGATCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  std::string expected = "Alice";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-1-test-2", "[test-strs-1-test-2]") {
  std::string dna_database = "./tests/dna_databases/test-strs-1.dat";
  std::string dna_sequence =
      "AACCCTGCGCGCGCGCGATCTATCTATCTATCTATCCAGCATTAGCTAGCATCAAGATAGATAGATGAATTT"
      "CGAAATGAATGAATGAATGAATGAATGAATG";
  std::string expected = "Bob";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-1-test-3", "[test-strs-1-test-3]") {
  std::string dna_database = "./tests/dna_databases/test-strs-1.dat";
  std::string dna_sequence =
      "CCAGATAGATAGATAGATAGATAGATGTCACAGGGATGCTGAGGGCTGCTTCGTACGTACTCCTGATTTCGG"
      "GGATCGCTGACACTAATGCGTGCGAGCGGATCGATCTCTATCTATCTATCTATCTATCCTATAGCATAGACA"
      "TCCAGATAGATAGATC";
  std::string expected = "Charlie";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-1-test-4", "[test-strs-1-test-4]") {
  std::string dna_database = "./tests/dna_databases/test-strs-1.dat";
  std::string dna_sequence =
      "GGTACAGATGCAAAGATAGATAGATGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGA"
      "ATGACACACGTCGATGCTAGCGGCGGATCGTATATCTATCTATCTATCTATCAACCCCTAG";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-2-test-1", "[test-strs-2-test-1]") {
  std::string dna_database = "./tests/dna_databases/test-strs-2.dat";
  std::string dna_sequence =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  std::string expected = "Casey";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-2-test-2", "[test-strs-2-test-2]") {
  std::string dna_database = "./tests/dna_databases/test-strs-2.dat";
  std::string dna_sequence =
      "TATTATTATTATAACCCTGCGCGCGCGCGATCCAGCATTAGCTAGCATCAAGATGAGATGAGATGGAATTTC"
      "GAAATGAATGAATGAATGAATGAATGAATG";
  std::string expected = "Amani";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-2-test-3", "[test-strs-2-test-3]") {
  std::string dna_database = "./tests/dna_databases/test-strs-2.dat";
  std::string dna_sequence =
      "AATGCCAGATGAGATGAGATGAGATGAGATGAGATGGTCACAGGGATGCTGAGGGCTGCTTCGTACGTACTC"
      "CTGATTTCGGGGATCGCTGACACTCGTGCGAGCGGATCGATCTCTATTATTATTATTATCTATAGCATAGAC"
      "ATCCAGATGAGATGAGATGC";
  std::string expected = "Blair";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-2-test-4", "[test-strs-2-test-4]") {
  std::string dna_database = "./tests/dna_databases/test-strs-2.dat";
  std::string dna_sequence =
      "GGTACAGATGGCAAAGATGAGATGAGATGGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGA"
      "ATGAATGACACACGTCGATGCTAGCGGCGGATCGTATATTTATAACCCCTAG";
  std::string expected = "Ashley";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-2-test-5", "[test-strs-2-test-5]") {
  std::string dna_database = "./tests/dna_databases/test-strs-2.dat";
  std::string dna_sequence =
      "GGTACAGATGCAAAGATAGATAGATGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGA"
      "ATGACACACGTCGATGCTAGCGGCGGATCGTATATCTATCTATCTATCTATCAACCCCTAG";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-3-test-1", "[test-strs-3-test-1]") {
  std::string dna_database = "./tests/dna_databases/test-strs-3.dat";
  std::string dna_sequence =
      "AACCCTGCGCGCGCGCGATCATTAATTAATTAATTAATTACAGCATTAGCTAGCATCACACACACACACAGA"
      "ATTTCGACACCCACCCACCCACCCACCCACCCACC";
  std::string expected = "Denny";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-3-test-2", "[test-strs-3-test-2]") {
  std::string dna_database = "./tests/dna_databases/test-strs-3.dat";
  std::string dna_sequence =
      "ATTAATTAATTAATTAATTACCCACACACACACACACACACACACAGTCACAGGGATGCTGAGGGCTGCTTC"
      "GTACGTACTCCTGATTTCGGGGATCGCTGACACTCACCCGTGCGAGCGGATCGATCTCCTATAGCATAGACA"
      "TCCCACACACACACACCACACACACACACACACACACACACACACACACACCCACCCACCCACCCACCCACC"
      "CACCCACCCACCATTAATTAATTAATTAATTAATTAATTAATTAATTAATTAATTAATTA";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-3-test-3", "[test-strs-3-test-3]") {
  std::string dna_database = "./tests/dna_databases/test-strs-3.dat";
  std::string dna_sequence =
      "GGTACAGATGCAAAGATAGATAGATGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGA"
      "ATGACACACGTCGATGCTAGCGGCGGATCGTATATCTATCTATCTATCTATCAACCCCTAG";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-3-test-4", "[test-strs-3-test-4]") {
  std::string dna_database = "./tests/dna_databases/test-strs-3.dat";
  std::string dna_sequence =
      "CACACACACACACACACACACACAGGCATAGTTCGAGGAGAAATATCCGGGGCCCACCCACACACACACAAT"
      "TAATTAATTAAAAGACAACCAGCATATTAATTAATTAATTAATTACTCGGGTCTTGCCCAACCCGATTAATT"
      "AATTAATTA";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-4-test-1", "[test-strs-4-test-1]") {
  std::string dna_database = "./tests/dna_databases/test-strs-4.dat";
  std::string dna_sequence = "AGAGAGAGAAGAAGA";
  std::string expected = "Michael";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}

TEST_CASE("test-strs-5-test-1", "[test-strs-5-test-1]") {
  std::string dna_database = "./tests/dna_databases/test-strs-5.dat";
  std::string dna_sequence = "TATATTATAGAAGA";
  std::string expected = "Michael";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}
TEST_CASE("simple test case","[simple]"){
  std::string dna_database = "test-6.dat";
  std::string dna_sequence = "ATATAATA";
  std::string expected = "No match";
  REQUIRE(ProfileDNA(dna_database, dna_sequence) == expected);
}