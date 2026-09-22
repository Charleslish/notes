#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <istream>
#include <vector>
#include <limits>

// Reads one reading per line from in.
//
// A line whose leading characters form an integer contributes that integer.
// A line whose leading characters do not form an integer contributes nothing
// and is skipped in full, and reading continues with the following line.
// Anything left on a line after its integer is discarded.
//
// Returns the integers contributed, in the order the lines supplied them.
// A stream holding no lines, and a stream in which no line contributes,
// each give an empty vector.
std::vector<int> ReadReadings(std::istream& in);

#endif  // closes the include guard
