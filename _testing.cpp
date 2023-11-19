#include <iostream>

#include "stringc.h"
#include "vec.h"
#include "mathc.h"

struct Point {
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
};

int main() {
    stringc::String x = "Hello!x86World!x86SUII69";
    std::cout << x.contains("69") << std::endl;
    return 0;
}