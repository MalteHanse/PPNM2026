#include<iostream>
#include<cmath>
#include<vector>
#include<functional>
#include<fstream>
#include"matrix.hpp"
#include"newton.hpp"


std::vector<double> linspace(double start, double stop, int num) {
    std::vector<double> result;

    if (num == 1) {
        result.push_back(start);
        return result;
    }

    double step = (stop - start) / (num - 1);

    for (int i = 0; i < num; ++i) {
        result.push_back(start + i * step);
    }

    return result;
}

struct ann{
    int n; /* number of hidden neurons */
    std::function<double(double)> f = [](double x) { /* activation function */
        return x*std::exp(-x*x);
    };

    pp::vector p; /* network parameters: 3 per hidden neuron (center, width, weight) */
    ann(int n) : n(n) {
        p.resize(3*n);
        for(int i=0; i<n; i++) {
            p[3*i] = 0.0;     // center
            p[3*i+1] = 1.0;   // width
            p[3*i+2] = 1.0;   // weight
        }
    }
    double forward(double x) const {
        /* return the response of the network to the input signal x */
        double y = 0;
        for (int i=0; i<n; i++) {
            double center = p[3*i];
            double width = p[3*i+1];
            double weight = p[3*i+2];
            y += f((x - center) / width) * weight;
        }
        return y;
    };
    int train(pp::vector xs, pp::vector ys, int epochs=100){
        /* train the network to interpolate the given table {x,y} */
        std::function<double(pp::vector)> cost_function = [this, &xs, &ys](pp::vector params) {
            double cost = 0;
            for (int i=0; i<(int)xs.size(); i++) {
                double y_pred = 0;
                for (int j=0; j<n; j++) {
                    double center = params[3*j];
                    double width = params[3*j+1];
                    double weight = params[3*j+2];
                    y_pred += f((xs[i] - center) / width) * weight;
                }
                double error = y_pred - ys[i];
                cost += error * error;
            }
            return cost;
        };
        p = pp::newton(cost_function, p, 0.001, epochs);
        return 0;
    };
};

int main() {
    // PART A
    std::cout << "----------PART A-----------" << std::endl;
    auto g = [](double x) {
        return std::cos(5 * x - 1) * std::exp(- x * x);
    };
    // sample 50 points
    std::vector xs_std = linspace(-1, 1, 50);
    pp::vector xs(xs_std.size());
    pp::vector ys(xs.size());
    for (int i=0; i<=(int)xs.size(); i++) {
        xs[i] = xs_std[i];
        ys[i] = g(xs[i]);
    }

    // initialize network and train
    ann network(10);
    network.train(xs, ys, 3000);

    // save the result to file for plotting
    std::vector xs_plot = linspace(-1, 1, 200);
    std::ofstream network_out("network.dat");
    for (int i=0; i<(int)xs_plot.size(); i++) {
        if (i<=(int)xs.size()) {
            network_out << xs_plot[i] << " " 
            << network.forward(xs_plot[i]) << " "
            << g(xs_plot[i]) << " "
            << xs[i] << " "
            << ys[i] << std::endl; 
        }
        else {
            network_out << xs_plot[i] << " " 
            << network.forward(xs_plot[i]) << " "
            << g(xs_plot[i]) << std::endl;
        }
    }
    network_out.close();




    // PART B
    std::cout << "----------PART B-----------" << std::endl;


    // PART C
    std::cout << "----------PART C-----------" << std::endl;

    return 0;
}