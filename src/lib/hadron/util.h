#pragma once

#include <algorithm>
#include <vector>

namespace hadron {

    /**
     * @brief Removes all occurrences of a specified value from a vector.
     *
     * @tparam T The type of elements in the vector.
     * @param v The vector from which to remove the value.
     * @param value The value to be removed from the vector.
     */
    template <typename T>
    void RemoveByValue(std::vector<T>& v, T value)
    {
        v.erase(std::remove(v.begin(), v.end(), value), v.end());
    }

}