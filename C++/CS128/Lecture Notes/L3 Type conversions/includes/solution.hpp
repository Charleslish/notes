#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// Returns the average of two whole scores, keeping any half.
// AverageOfTwo(86, 83) returns 84.5. AverageOfTwo(20, 18) returns 19.0.
double AverageOfTwo(int first, int second);
// Returns the whole-number part of a value, discarding anything after the
// decimal point. WholeNumberPart(84.9) returns 84. WholeNumberPart(-3.98)
// returns -3.
int WholeNumberPart(double value);
#endif
