#pragma once

#include <cstddef>
#include <numeric>
#include <span>
#include <stdexcept>

inline int largest(std::span<const int> values) {
    if (values.empty()) {
        throw std::invalid_argument("The array must contain at least one value.");
    }
    int result = values.front();
    for (int value : values) {
        if (value > result) result = value;
    }
    return result;
}

inline int smallest(std::span<const int> values) {
    if (values.empty()) {
        throw std::invalid_argument("The array must contain at least one value.");
    }
    int result = values.front();
    for (int value : values) {
        if (value < result) result = value;
    }
    return result;
}

inline double average(std::span<const int> values) {
    if (values.empty()) {
        throw std::invalid_argument("The array must contain at least one value.");
    }
    const long long total = std::accumulate(values.begin(), values.end(), 0LL);
    return static_cast<double>(total) / static_cast<double>(values.size());
}
