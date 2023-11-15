#include <iostream>

#include "stringc.h"
#include "vec.h"

struct Point {
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
};

int main() {
    stringc::String x = "Hello world";
    vec::Vec<Point> floats = {Point{1, 1}, Point{2, 2}, Point{3, 3}, Point{3, 3}, Point{3, 3}};

    floats.foreach([](Point p) {
        
    });

    std::cout << floats.length() << std::endl;

    return 0;
}