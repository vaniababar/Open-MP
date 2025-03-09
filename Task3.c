#include <iostream>
#include <cmath>
#include <omp.h> // OpenMP Library

using namespace std;

const int NUM_INTERVALS = 1000000; // Number of intervals
const double A = 0.0, B = 1.0; // Integration range
const int NUM_THREADS = 4; // Number of threads (adjustable)

// Function to integrate (example: f(x) = x^2)
double function(double x) {
    return x * x;
}

// Simple Parallel Trapezoidal Rule Integration
double parallelTrapezoidalRule(double a, double b, int n, int num_threads) {
    double h = (b - a) / n; // Step size
    double integral = (function(a) + function(b)) / 2.0;
    
    #pragma omp parallel for num_threads(num_threads) reduction(+:integral)
    for (int i = 1; i < n; i++) {
        integral += function(a + i * h);
    }

    integral *= h;
    return integral;
}

int main() {
    double start = omp_get_wtime();
    double result = parallelTrapezoidalRule(A, B, NUM_INTERVALS, NUM_THREADS);
    double end = omp_get_wtime();

    cout << "Integral Result: " << result << endl;
    cout << "Execution Time: " << fixed << (end - start) << " seconds" << endl;

    return 0;
}
