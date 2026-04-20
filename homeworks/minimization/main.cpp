#include<iostream>
#include<vector>
#include<cmath>
#include<functional>
#include"matrix.hpp"
#include"qr.hpp"

// Python implementations
// def newton(φ,x,acc=1e-3) :
//     while True :                    # Newton iterations
//         g = gradient(φ,x)
//         if g.norm() < acc : break   # job done
//         H = hessian(φ,x)
//         dx = QRdecomposition(H).solve(-g)
//         λ = 1 ;
//         while λ ≥ 1/1024 :       # backtracking linesearch
//             if φ(x+λ*dx) < φ(x) : break # good step
//             λ /= 2
//         x=x+λ*dx
//     return x

// def gradient(φ,x) :
//     φx = φ(x)
//     gφ = vector(len(x))
//     for i in range(len(x)) :
//         dxi = (1+abs(x[i]))*2**(-26)
//         x[i]+=dxi
//         gφ[i]=(φ(x)-φx)/dxi
//         x[i]-=dxi
//     return gφ

// def hessian(φ,x) :
//     H = matrix(len(x),len(x))
//     gφx = gradient(φ,x)
//     for j in range(len(x)) :
//         dxj=(1+abs(x[j]))*2**(-13)
//         x[j]+=dxj
//         dgφ=gradient(φ,x)-gφx
//         for i in range(len(x)) : H[i,j]=dgφ[i]/dxj
//         x[j]-=dxj
//     return H

pp::vector gradient(
    std::function<double(pp::vector)> f,
    pp::vector x
) {
    double fx = f(x);
    pp::vector gf ((int)x.size());

    for (int i=0; i<(int)x.size(); i++) {
        double dxi = (1 + std::abs(x[i])) * std::pow(2, -26);
        x[i] += dxi;
        gf[i] = (f(x) - fx) / dxi;
        x[i] -= dxi;
    }
    return gf;
}

pp::matrix hessian(
    std::function<double(pp::vector)> f,
    pp::vector x
) {
    int x_size = x.size();
    pp::matrix H(x_size, x_size);
    pp::vector gfx = gradient(f, x);

    for (int j=0; j<x_size; j++) {
        double dxj = (1 + std::abs(x[j])) * std::pow(2, -13);
        x[j] += dxj;
        pp::vector dgf = gradient(f, x) - gfx;
        for (int i=0; i<x_size;i++) {
            H[i, j] = dgf[i] / dxj;
        }
        x[j] -=dxj;
    }
    return H;
}

pp::vector newton(
    std::function<double(pp::vector)> f,
    pp::vector x,
    double acc=1e-3
) {
    int counter = 0;
    while (counter < 1000) {
        pp::vector g = gradient(f, x);
        if (g.norm() < acc) break;
        pp::matrix H = hessian(f, x);
        pp::QR QRH;
        auto [Q, R] = QRH.decomp(H);
        pp::vector dx = QRH.solve(Q, R, -g);
        double lambda = 1;
        while (lambda >= 1.0/1024) {
            if (f(x + lambda * dx) < f(x)) break;
            lambda /= 2;
        }
        x = x + lambda * dx;
        counter++;
    }
    return x;
}

int main() {
    // PART A
    std::cout << "-----------PART A-------------" << std::endl;
    int counter_rosen = 0;
    auto rosenbrock = [&counter_rosen](pp::vector v) {
        double x = v[0];
        double y = v[1];
        double f = (1 - x) * (1 - x) + 100 * (y - x * x) * (y - x * x);
        counter_rosen++;
        return f;
    };
    int counter_himmel = 0;
    auto himmelblau = [&counter_himmel](pp::vector v) {
        double x = v[0];
        double y = v[1];
        double f = (x * x + y - 11) * (x * x + y - 11) + (x + y * y - 7) * (x + y * y - 7);
        counter_himmel++;
        return f;
    };

    // find minimum of rosenbrock
    pp::vector rosen_start {0.5, 1.5};
    pp::vector min_rosen = newton(rosenbrock, rosen_start);

    // find minimum of himmelblau
    pp::vector himmel_start {6.3, 6.4};
    pp::vector min_himmel = newton(himmelblau, himmel_start);

    min_rosen.print("Rosenbrock minimum at: ");
    std::cout << "Found with " << counter_rosen << " evaluations. Analytic minimum rosenbrock: (1.0, 1.0)" << std::endl;
    min_himmel.print("Himmelblau minimum at: ");
    std::cout << "Found with " << counter_himmel << " evaluations. Analytic minimum Himmelblau: (3.0, 2.0)" << std::endl;

    // PART B
    std::cout << "----------PART B--------------" << std::endl;



    return 0;
}