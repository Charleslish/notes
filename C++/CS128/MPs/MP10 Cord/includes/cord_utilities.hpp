#ifndef CORD_UTILITIES_HPP
#define CORD_UTILITIES_HPP

#include "cord.hpp"
#include "shared_pointer.hpp"

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord);

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx);

#endif
