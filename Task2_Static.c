#include <iostream>
#include <cmath>
#include <omp.h> // OpenMP Library

using namespace std;

const int NUM_INTERVALS = 1000000; // Number of intervals
const double A = 0.0, B = 1.0; // Integration range
const int NUM_THREADS = 8; // Number of threads (adjustable)

// Function to integrate (example: f(x) = x^2)
double function(double x) {
    return x * x;
}

// Parallel Trapezoidal Rule Integration with Static Scheduling
double parallelTrapezoidalRuleStatic(double a, double b, int n, int num_threads) {
    double h = (b - a) / n; // Step size
    double integral = (function(a) + function(b)) / 2.0;

    #pragma omp parallel for num_threads(num_threads) reduction(+:integral) schedule(static)
    for (int i = 1; i < n; i++) {
        integral += function(a + i * h);
    }

    integral *= h;
    return integral;
}

int main() {
    // Parallel Execution (Static Scheduling)
    double start_par_static = omp_get_wtime();
    double result_par_static = parallelTrapezoidalRuleStatic(A, B, NUM_INTERVALS, NUM_THREADS);
    double end_par_static = omp_get_wtime();
    
    // Output Results
    cout << "Integral Result (Parallel - Static Scheduling): " << result_par_static << endl;
    cout << "Parallel Execution Time (Static): " << fixed << (end_par_static - start_par_static) << " seconds" << endl;
    
    return 0;
}
