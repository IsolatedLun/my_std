#include <iostream>

#include "stringc.h"
#include "vec.h"
#include "mathc.h"
#include <cmath>

struct Point {
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
};

int main() {
    vec::Vec<stringc::String> vec;

    std::cout << std::ceil(mathc::PI) << std::endl;
    std::cout << mathc::ceil(mathc::PI) << std::endl;

    std::cout << "------" << std::endl;

    std::cout << std::floor(-mathc::PI) << std::endl;
    std::cout << mathc::floor(-mathc::PI) << std::endl;
    return 0;
}