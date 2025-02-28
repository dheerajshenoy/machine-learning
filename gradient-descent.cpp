#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

// Original function
double Y(const double &x) noexcept {
    return 2 * x + 3;
}

// Test function
double y(const double &w, const double &b, const double &x) noexcept {
    return w * x + b;
}

// Cost function
double J(const double &w, const double &b, const std::vector<double> &points) noexcept {
    double sum = 0.0f;
    int m = points.size();

    for (size_t i=0; i < m; i++) {
        auto x = points.at(i);
        sum += pow(y(w, b, x) - Y(x), 2);
    }

    return sum / ( 2 * m);
}

double pdiff_w(const std::function<double(double, double, std::vector<double>)> &f,
               const double &w, const double &b, const std::vector<double> &points) noexcept {
    double h = 1e-10;
    return ( f(w + h, b, points) - f(w - h, b, points) ) / (2 * h);
}

double pdiff_b(const std::function<double(double, double, std::vector<double>)> &f,
               const double &w, const double &b, const std::vector<double> &points) noexcept {
    double h = 1e-10;
    return ( f(w, b + h, points) - f(w, b - h, points) ) / (2 * h);
}


void gradient_descent(const std::vector<double> &points, double learning_rate = 0.01) noexcept {
    double w = 1.0, b = 1.0;
    double tmp_w, tmp_b;

    while (true) {

        tmp_w = w - learning_rate * pdiff_w(J, w, b, points);
        tmp_b = b - learning_rate * pdiff_b(J, w, b, points);

        if (std::abs(tmp_w - w) < 1e-10 && std::abs(tmp_b - b) < 1e-10) {
            std::cout << "w = " << w << " b = " << b << "\n";
            break;
        }

        w = tmp_w;
        b = tmp_b;

    }
}

int main(int argc, char *argv[]) {
    std::vector<double> points = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Without gradient descent
    // for (int w = 0; w < 10; w++) {
    //     for (int b = 0; b < 10; b++) {
    //         std::cout << "W = " << w << " B = " << b << " J = " << J(w, b, points) << "\n";
    //     }
    // }

    // With gradient descent
    gradient_descent(points);

    return 0;
    }
