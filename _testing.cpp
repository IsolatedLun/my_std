#include <iostream>

#include "stringc.h"
#include "vec.h"

struct Point {
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
};

int main() {
    Vec<Point> points = {Point{1, 2}, Point{3, 4}};
    Vec<Point> other_points;
    for(int i = 0; i < 20; i++) {
        other_points.push(Point{0, 0});
    }

    points.extend(other_points);
    points.foreach([](Point p) {
        std::cout << "Point: " << p.x << ", " << p.y << std::endl;
    });

    return 0;
}