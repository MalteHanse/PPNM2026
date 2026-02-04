#include<iostream>
#include"vec.h"

int main() {
    vec v = vec(1, 2, 3);
    vec w = vec(0.5, -0.5, 1.5);

    std::cout << "----Print vector----" << std::endl;
    v.print("v = ");
    w.print("w = ");

    std::cout << "----Add----" << std::endl;
    vec a = vec(v.x + w.x, v.y + w.y, v.z + w.z);
    a.print("v + w = ");

    std::cout << "----subtract----" << std::endl;
    vec b = vec(v.x - w.x, v.y - w.y, v.z - w.z);
    b.print("v - w = ");

    std::cout << "----multiply----" << std::endl;
    vec c = vec(v.x * 2, v.y * 2, v.z * 2);
    c.print("2 * v = ");

    std::cout << "----norm----" << std::endl;
    std::cout << "norm = " << v.norm() << std::endl;

    std::cout << "----cross-product----" << std::endl;
    vec x = v.cross(w);
    x.print("v x w = ");

    std::cout << "----dot-product----" << std::endl;
    double y = v.dot(w);
    std::cout << "v * w = " << y << std::endl;
    return 0;
}