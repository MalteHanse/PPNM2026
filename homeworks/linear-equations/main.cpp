#include"matrix.hpp" 
#include<vector> 
#include<iostream> 
#include<random>


pp::matrix random_matrix(int n, int m) {
    if (n <= m) {
        throw std::invalid_argument("Require n > m");
    }

    // Random device for seeding
    std::random_device rd;

    // Mersenne Twister engine
    std::mt19937 gen(rd());

    // Uniform distribution between 0 and 1
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    pp::matrix A(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A.cols[j][i] = dist(gen);
        }
    }

    return A;
}

pp::vector random_vector(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    pp::vector b(n);

    for (int j; j<n; j++) {
        b[j] = dist(gen);
    }
    return b;
}

struct QR{
    std::pair<pp::matrix, pp::matrix>  decomp(const pp::matrix& A) {
        pp::matrix Q = A.copy();
        pp::matrix R(A.size2(), A.size2());
        // orthogonalize Q and fill-in R
        int m = A.size2();
        for (int i = 0; i < m; ++i) {
            pp::vector v = A[i];
            for (int j = 0; j < i; ++j) {
                double r = v.dot(Q[j]);  // project updated v, not original A[i]
                R(j, i) = r;
                v = v - r * Q[j];
            }

            double norm_v = v.norm();
            R[i][i] = norm_v;
            Q[i] = v / norm_v;
        }
        return {Q, R};
    }

    pp::vector solve(const pp::matrix& Q, const pp::matrix& R, const pp::vector& b) {
        // since QRx=b => Q^TQRx=Q^Tb => Rx=Q^Tb
        // so we start by compting Q^T * b = y
        pp::vector y(Q.size2());
        for (int i; i<Q.size2(); i++){
            y[i] = Q[i].dot(b);
        }
        // pp::vector y = Q.transpose() * b;
        // and now we can calculate each element x_i in x
        pp::vector x(R.size2());
        for (int i = R.size2() - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < R.size2(); j++) {
                sum += R[i][j] * x[j];
                }

            x[i] = (y[i] - sum) / R[i][i];
            }
        return x;
        }
    // double det(const pp::matrix& R) {
    //     // ...
    // }

    // pp::matrix inverse(const pp::matrix& Q, const pp::matrix& R) {
    //     // ...
    // }
};

int main() {
    int n = 5;
    int m = 4;

    // generate random matrix
    pp::matrix A = random_matrix(n, m);

    A.print("A=");
    
    // initialize QR
    QR qr;
    auto [Q, R] = qr.decomp(A);

    // check if it works
    std::cout << "------Checking decomp function---------" << std::endl;
    Q.print("Q=");

    // check if R is upper triangular
    R.print("R=");

    // check if QR = A
    pp::matrix QR = Q * R;
    QR.print("Q * R = A = ");

    // check if Q^T Q = I
    pp::matrix eye = Q.transpose() * Q;
    eye.print("Q^T * Q=");

    // generate random vector
    // check if solve works
    std::cout << "-----Checking solve function-----" << std::endl;
    pp::vector b = random_vector(A.size1());
    b.print("b= ");
    pp::vector x = qr.solve(Q, R, b);
    x.print("x= ");
    pp::vector Ax = A * x;
    Ax.print("A * x = ");
    std::cout << "approx(A*x, b)= " << pp::approx(b, Ax) << std::endl;



    return 0;
}