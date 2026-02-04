#include<iostream>
#include<cstudio>
#include<vector>

int main () {
    double a = 1.0;
    double b = a;
    std::vector<double> v{1, 2, 3};
    auto u = v;
    auto& w = v;
    return 0;
}