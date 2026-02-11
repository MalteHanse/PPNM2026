#include<iostream>
#include"vec.h"

int main() {
    vec v = vec(1.0, 2.0, 3.0);
    vec w = vec(0.5, -0.5, 1.5);

    std::cout << "----Print vector----" << std::endl;
    v.print("v = ");
    w.print("w = ");

    std::cout << "----Add----" << std::endl;
    vec a = v + w;
    a.print("v + w = ");

    std::cout << "----subtract----" << std::endl;
    vec b = v - w;
    b.print("v - w = ");

    std::cout << "----multiply----" << std::endl;
    vec c = 2 * v;
    c.print("2 * v = ");

    std::cout << "----norm----" << std::endl;
    std::cout << "norm = " << v.norm() << std::endl;

    std::cout << "----cross-product----" << std::endl;
    vec x = v.cross(w);
    x.print("v x w = ");

    std::cout << "----dot-product----" << std::endl;
    double y = v.dot(w);
    std::cout << "v * w = " << y << std::endl;


    vec m = vec(1, 2, 3);
    vec n = vec(5, -5, 15);

    std::cout << "----Print vector----" << std::endl;
    m.print("m = ");
    n.print("n = ");

    std::cout << "----Add----" << std::endl;
    vec o = m + n;
    o.print("m + n = ");

    std::cout << "----subtract----" << std::endl;
    vec p = m - n;
    p.print("m - n = ");

    std::cout << "----multiply----" << std::endl;
    vec q = 2 * m;
    q.print("2 * m = ");

    std::cout << "----norm----" << std::endl;
    std::cout << "norm = " << m.norm() << std::endl;

    std::cout << "----cross-product----" << std::endl;
    vec r = m.cross(n);
    r.print("v x w = ");

    std::cout << "----dot-product----" << std::endl;
    double s = m.dot(n);
    std::cout << "v * w = " << s << std::endl;
    return 0;
}