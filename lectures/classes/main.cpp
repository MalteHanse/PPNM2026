#include<iostream>
// #include<cstudio>
#include<vector>
#include<cstdio>
#include"vec.h"

int main () {
    // double a = 1.0;
    // double b = a;
    // if (a == b) {
    //     std::cout << "a==b" << std::endl; 
    // }
    // else {
    //     std::cout << "a != b" << std::endl;
    // }
    // std::vector<double> v{1, 2, 3};
    // for (size_t i=0; i < v.size(); i++) {
    //     std::cout << v[i] << std::endl;
    // }
    // for (auto vi : v) {
    //     std::cout << vi << std::endl;
    // }
    // auto u = v;
    // auto& w = v;

    // size_t i = 0;
    // while (i < v.size()) {
    //     std::cout << v[i] << std::endl;
    //     i++;
    // }

    // i = 0;

    // do {
    //     std::cout << v[i] << std::endl;
    //     i++;
    // } while (i < v.size());
    // return 0;

    pp::vec alpha {1, 2, 3};
    alpha.x = 6;
    std::cout << alpha.x << " " << alpha.y << " " << alpha.z << std::endl;;
}