#pragma once
#include<iostream>
#include<cmath>

bool approx(double a, double b, double acc=1e-9, double eps=1e-9) {
    double absolute = std::abs(a - b);
    double relative = absolute / std::max(std::abs(a), std::abs(b));
    if (absolute <= acc || relative <= eps) {
        return true;
    }
    else {
        return false;
    }
}

struct vec{
    double x, y, z;

    // constructers
    vec(double x, double y, double z) : x(x), y(y), z(z) {}     // parameterized ctor
    vec() : vec(0, 0, 0) {}                                       // unparametrized ctor
    vec(const vec&) = default;                                  // copy
    vec(vec&&) = default;                                       // move
    ~vec() = default;                                           // destructer
    
    // assigments
    vec& operator=(const vec&) = default;                       // copy assignment
    vec& operator=(vec&&) = default;                            // move assignment

    // arithmetic
    vec& operator+=(const vec&);
    vec& operator-=(const vec&);
    vec& operator*=(double);
    vec& operator/=(double);

    // utility
    void set(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }

    // debugging
    void print(const std::string& s = "") const;

    bool approx(const double a, const double b) const;
    bool approx(const vec& a, const vec& b) {
        if (approx(a.x, b.x)) {
            return false;
        }
        if (!approx(a.y,b.y)) {
            return false;
        }
        if (!approx(a.z,b.z)) {
            return false;
        }
        return true;
	}

    // std::ostream& operator<<(std::ostream& os, const vec& v) {
    //     os << "{ " << v.x << ", " << v.y << ", " << v.z << " } ";
    //     return os;
    // }

    // dot-product
    // double dot(const vec& a, const vec& b) {
    //     double sum = std::sum(a * b);
    //     return sum;
    // }

    // cross-product
    // vec cross(const vec& a, const vec& b) {
    //     double x = a[1] * b[2] - a[2] * b[1];
    //     double y = a[2] * b[0] - a[0] * b[2];
    //     double z = a[0] * b[1] - a[1] * b[0];
    //     return vec(x, y, z);
    // }

    // norm
    // double norm(const vec& v) {
    //     double length = std::sqrt(std::pow(v[0], 2) + std::pow(v[1], 2) + std::pow(v[2], 2));
    //     return length;
    // }
};

void vec::print(std::string s) const {
    std::cout << s << x << " " << y << " " << z << std::endl;
}

// non-memeber operators
vec operator-(const vec&);
vec operator-(const vec&, const vec&);
vec operator+(const vec&, const vec&);
vec operator*(const vec&, double);
vec operator*(double, const vec&);
vec operator/(const vec&, double);

