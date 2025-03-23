#include <iostream>
#include <cmath>
#include <omp.h> // OpenMP Library

using namespace std;

const int NUM_INTERVALS = 3000000; // Number of intervals
const double A = 0.0, B = 1.0; // Integration range
const int NUM_THREADS = 8; // Number of threads (adjustable)

// Function to integrate (example: f(x) = x^2)
double function(double x) {
    return x * x;
}

// Parallel Trapezoidal Rule Integration with Dynamic Scheduling and Chunk Size
double parallelTrapezoidalRule(double a, double b, int n, int num_threads) {
    double h = (b - a) / n; // Step size
    double integral = (function(a) + function(b)) / 2.0;
    
    #pragma omp parallel for num_threads(num_threads) reduction(+:integral) schedule(dynamic, 2000)
    for (int i = 1; i < n; i++) {
        integral += function(a + i * h);
    }

    integral *= h;
    return integral;
}

int main() {
    double total_time = 0.0;
    double result_par = 0.0;

    // Run the integration 10 times and calculate average execution time
    for (int i = 0; i < 10; i++) {
        double start_par = omp_get_wtime();
        result_par = parallelTrapezoidalRule(A, B, NUM_INTERVALS, NUM_THREADS);
        double end_par = omp_get_wtime();
        
        double execution_time = end_par - start_par;
        total_time += execution_time;

        cout << "Run " << i + 1 << " Execution Time: " << fixed << execution_time << " seconds" << endl;
    }

    // Calculate and display the average execution time
    double average_time = total_time / 10.0;
    cout << "\nIntegral Result (Parallel - Dynamic Scheduling, Chunk Size = 2000): " << result_par << endl;
    cout << "Average Execution Time over 10 Runs: " << fixed << average_time << " seconds" << endl;

    return 0;
}
