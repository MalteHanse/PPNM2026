#pragma once
#include<string>
#include<vector>
#include<iostream>

namespace pp{
    struct vector{
        std::vector<double> data;
        vector() = default;
        vector(int n) : data(n) {}
        vector(vector&) = default;
        vector(vector&&) = default;
        ~vector() = default;

        int size() const {return data.size();}
        double& operator[](int i) {return data[i];}

        void print(std::string s="") {
            std::cout << s << " ";
            for(double& d : data) {
                std::cout << d << " ";
                std::cout << "\n";
            }
        }
        vector& operator+=(const vector& other) {
            for (int i=0; i<size();i++) {
                (*this)[i] += other[i];
            }
            return *this;
        }
    };
}