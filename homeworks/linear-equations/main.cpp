#include"matrix.hpp" 
#include<vector> 
#include<iostream> 
#include<random>


pp::matrix random_matrix(int n, int m) {
    if (n <= m) {
        throw std::invalid_argument("Require n < m");
    }

    // Random device for seeding
    std::random_device rd;

    // Mersenne Twister engine
    std::mt19937 gen(rd());

    // Uniform distribution between 0 and 1
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    pp::matrix A(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            A.cols[i][j] = dist(gen);
        }
    }

    return A;
}

struct QR{
    pp::matrix decomp(const pp::matrix& A) {
        pp::matrix Q = A.copy();
        pp::matrix R(A.size2(), A.size2());
        // orthogonalize Q and fill-in R
        int m = A.size2();
        for (int i = 0; i < m; ++i) {
            pp::vector v = A[i];
            for (int j = 0; j < i; ++j) {
                double r = Q[j].dot(A[i]);
                R(j, i) = r;
                v = v - r * Q[j];
            }

            double norm_v = v.norm();
            R[i][i] = norm_v;
            Q[i] = v / norm_v;
    }
        return Q, R;
    }

    pp::vector solve(const pp::matrix& Q, const pp::matrix& R, const pp::vector& b) {
        // ...
    }

    double det(const pp::matrix& R) {
        // ...
    }

    pp::matrix inverse(const pp::matrix& Q, const pp::matrix& R) {
        // ...
    }
};

int main() {
    int n = 5;
    int m = 4;
    pp::matrix A = random_matrix(n, m);
    A.print("A=");
    return 0;
}