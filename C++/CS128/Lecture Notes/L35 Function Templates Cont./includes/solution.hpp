
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <stdexcept>
#include <utility>
#include <vector>

template <typename To, typename From>
To Lookup(const std::vector<std::pair<From, To>>& entries, const From& key) {
    for (const auto& entry : entries) 
        if (entry.first == key) 
            return entry.second;
    throw std::runtime_error("Key not found");
}

#endif