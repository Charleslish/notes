#ifndef SOLUTION_HPP
#define SOLUTION_HPP

struct Climb {
  unsigned int start = 0;
  unsigned int length = 0;
};

unsigned int CountSummits(const int* elevations, unsigned int size);
Climb LongestClimb(const int* elevations, unsigned int size);
void SmoothInPlace(int* elevations, unsigned int size);
const int* HighestPoint(const int* first, const int* last);

bool IsSummit(const int* elevations, unsigned int index, unsigned int plateau_end);

unsigned int FindPlateauEnd(const int* elevations, unsigned int start, unsigned int size);

#endif
