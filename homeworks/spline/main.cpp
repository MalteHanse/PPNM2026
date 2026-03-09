#include<stdexcept>
#include<vector>
#include<cmath>
#include<fstream>
#include"matrix.hpp"

pp::vector linspace(double start, double stop, int num) {
    pp::vector result(num);

    if (num == 1) {
        result[0] = start;
        return result;
    }

    double step = (stop - start) / (num - 1);

    for (int i = 0; i < num; ++i) {
        result[i] = start + i * step;
    }

    return result;
}

int binsearch(const pp::vector& x, double z) {
    /* locates the interval for z by bisection */
    if (z < x[0] || z > x[x.size() - 1]) {
        throw std::invalid_argument("invalid");
    }
    int i = 0, j = x.size() - 1;
    while (j - i > 1) {
        int mid = (i + j) / 2;
        if (z > x[mid]) i = mid; else j = mid;
    }
    return i;
}

struct lspline {
    pp::vector x, y;

    double linterp(const pp::vector& x, const pp::vector& y, double z) {
        int i = binsearch(x, z);
        double dx = x[i + 1] - x[i];
        if (!(dx > 0)) {
            throw std::invalid_argument("uups...");
        }
        double dy = y[i + 1] - y[i];
        return y[i] + dy / dx * (z - x[i]);
    }

    double linterpInteg(const pp::vector& x, const pp::vector& y, double z) {
        int i = binsearch(x, z);  // find which interval z falls in
        
        double sum = 0;
        
        // sum up the complete trapezoids before interval i
        for (int k = 0; k < i; k++) {
            double dx = x[k+1] - x[k];
            sum += dx * (y[k] + y[k+1]) / 2.0;  // trapezoid area
        }
        
        // add the partial trapezoid from x[i] to z
        double dx = z - x[i];
        double y_z = linterp(x, y, z);       
        sum += dx * (y[i] + y_z) / 2.0;         
        
        return sum;
    }

    // wrappers
    double evaluate(double z) {
        return linterp(x, y, z);
    }
    double integrate(double z) {
        return linterpInteg(x, y, z);
    }
};

struct qspline {
    pp::vector x, y, b, c;

    void qinterp(const pp::vector& xs, const pp::vector& ys) {
        int n = xs.size();
        x = xs;
        y = ys;
        b.resize(n - 1);
        c.resize(n - 1);

        c[0] = 0;
        for (int i = 0; i < n - 2; i++) {
            double dx  = x[i+1] - x[i];
            double dy  = y[i+1] - y[i];
            double dx1 = x[i+2] - x[i+1];
            double dy1 = y[i+2] - y[i+1];
            // Continuity of derivative: b[i] same from both sides
            // b[i] = (dy/dx) - c[i]*dx  and  b[i] = (dy1/dx1) - c[i+1]*dx1
            // Setting equal and solving for c[i+1]:
            c[i+1] = (dy1/dx1 - dy/dx + c[i]*dx) / dx1;
        }

        // Backward pass: average c to symmetrize
        // The forward pass started with c[0]=0, which biases the result.
        // Redo from the right end with c[n-2]=0 and average the two passes.
        pp::vector c2(n - 1);
        c2[n-2] = 0;
        for (int i = n - 3; i >= 0; i--) {
            double dx  = x[i+1] - x[i];
            double dy  = y[i+1] - y[i];
            double dx1 = x[i+2] - x[i+1];
            double dy1 = y[i+2] - y[i+1];
            c2[i] = (dy/dx - dy1/dx1 + c2[i+1]*dx1) / dx;
        }
        for (int i = 0; i < n - 1; i++) {
            c[i] = (c[i] + c2[i]) / 2.0;  // average the two passes
        }

        // Compute b coefficients from c
        for (int i = 0; i < n - 1; i++) {
            double dx = x[i+1] - x[i];
            double dy = y[i+1] - y[i];
            b[i] = dy/dx - c[i]*dx;
        }
    }

    double evaluate(double z) {
        /* evaluate the spline: y[i] + b[i]*(z-x[i]) + c[i]*(z-x[i])^2 */
        qinterp(x, y);
        int i = binsearch(x, z);
        double dx = z - x[i];
        return y[i] + b[i]*dx + c[i]*dx*dx;
    }

    double derivative(double z) {
        /* derivative: b[i] + 2*c[i]*(z-x[i]) */
        int i = binsearch(x, z);
        double dx = z - x[i];
        return b[i] + 2*c[i]*dx;
    }

    double integrate(double z) {
        /* analytic integral from x[0] to z */
        int i = binsearch(x, z);
        double sum = 0;

        for (int k = 0; k < i; k++) {
            double dx = x[k+1] - x[k];
            sum += y[k]*dx + b[k]*dx*dx/2.0 + c[k]*dx*dx*dx/3.0;
        }

        double dx = z - x[i];
        sum += y[i]*dx + b[i]*dx*dx/2.0 + c[i]*dx*dx*dx/3.0;
        return sum;
    }
};

int main() {
    // ---------------PART A-----------------
    // build the tabulated data
    pp::vector xs {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    pp::vector ys(xs.size());
    for (int i=0; i<xs.size(); i++) {
        ys[i] = std::cos(xs[i]);
    }

    lspline lspline;
    lspline.x = xs;
    lspline.y = ys;

    // save tabulated data
    std::ofstream table("tabulated.dat");
    for (int i=0; i<xs.size(); i++) {
        table << xs[i] << " " << ys[i] << std::endl;
    }
    table.close();

    // save interpolated data
    std::ofstream linterp("lspline.dat");
    pp::vector zs = linspace(xs[0], xs[xs.size() - 1], 100);
    for (int i=0; i<zs.size(); i++) {
        double z = lspline.evaluate(zs[i]);
        double s = lspline.integrate(zs[i]);

        linterp << zs[i] << " " << z << " " << s << std::endl;
    }
    linterp.close();

    //-----------PART B---------------
    qspline qspline;
    qspline.x = xs;
    qspline.y = ys;

    // save interpolated data
    std::ofstream qinterp("qspline.dat");
    pp::vector zs2 = linspace(xs[0], xs[xs.size() - 1], 100);
    for (int i=0; i<zs2.size(); i++) {
        std::cout << zs2[i] << std::endl;
        double z = qspline.evaluate(zs2[i]);
        double s = qspline.integrate(zs2[i]);

        qinterp << zs2[i] << " " << z << " " << s << std::endl;
    }
    qinterp.close();


    return 0;
}

