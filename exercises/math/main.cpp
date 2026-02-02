#include <iostream>
// #include <cstdlib>
#include "sfuns.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        double x = std::atof(argv[1]);
        std::cout << sfuns::lngamma(x) << '\n';
    }
}