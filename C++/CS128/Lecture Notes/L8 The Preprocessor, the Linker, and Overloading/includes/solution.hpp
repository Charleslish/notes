// Write this header yourself: the include guard first, then a declaration
// for every function in the activity's API table. Declarations only; the
// definitions belong in src/solution.cc.
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

int PercentFull(int level_liters, int capacity_liters);
int PercentFull(double level_meters, double tank_depth_meters);
int MinutesUntilEmpty(int level, int rate);

#endif