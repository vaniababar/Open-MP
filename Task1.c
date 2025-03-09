#include <iostream>
#include <cmath>
#include <chrono> // Chrono library for timing

using namespace std;
using namespace std::chrono; // For easier access to time functions

const int NUM_INTERVALS = 1000000; // Number of intervals
const double A = 0.0, B = 1.0; // Integration range

// Function to integrate (example: f(x) = x^2)
double function(double x) {
    return x * x;
}

// Sequential Trapezoidal Rule Integration
double sequentialTrapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n; // Step size
    double integral = (function(a) + function(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        integral += function(a + i * h);
    }

    integral *= h;
    return integral;
}

int main() {
    // Start measuring time
    auto start_seq = high_resolution_clock::now();

    // Run the integration function
    double result = sequentialTrapezoidalRule(A, B, NUM_INTERVALS);

    // Stop measuring time
    auto end_seq = high_resolution_clock::now();

    // Calculate execution time in seconds
    double exec_time = duration<double>(end_seq - start_seq).count();

    // Output results
    cout << "Integral Result: " << result << endl;
    cout << "Sequential Execution Time: " << fixed << exec_time << " seconds" << endl;

    return 0;
}
