#pragma once

namespace mathc {
    template<typename T>
    const T& min(T const& a, T const& b) {
        if(a < b) {
            return a;
        } else {
            return b;
        }
    }

    template<typename T>
    const T& max(T const& a, T const& b) {
        if(a > b) {
            return a;
        }

        return b;
    }

    template<typename T>
    const T& clamp(T const& min, T const& value, T const& max) {
        if(value < min) {
            return min;
        } else if (value > max) {
            return max;
        }

        return max;
    }
}