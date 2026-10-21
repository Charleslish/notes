#ifndef LARGER_HPP
#define LARGER_HPP

template <typename T>
T Larger(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#endif