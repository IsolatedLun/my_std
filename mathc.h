#pragma once

namespace mathc {
    double PI = 3.141592653589793;


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

    template<typename T>
    T ceil(T const& a) {
        if(a - int(a) == 0)
            return a;
            
        int sign = a < 0 ? 0 : 1;
        return int(a) + sign;
    }

    template<typename T>
    T floor(T const& a) {
        if(a - int(a) == 0)
            return a;
            
        int sign = a < 0 ? 1 : 0;
        return int(a) - sign;
    }
}