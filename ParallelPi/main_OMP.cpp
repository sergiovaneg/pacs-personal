#include <omp.h>

#include <iostream>
#include <cmath>
#include <iomanip>

int main (int argc, char** argv){
    const unsigned n = (argc == 2) ? std::stoul(argv[1]) : 1e6;
    const double h = 1./n;

    double sum = 0.;
    #pragma parallel for reduction(+ : sum)
        for(unsigned i = 0; i < n; ++i){
            double x = h * (i + 0.5);
            sum += 4 / (1 + x * x);
        }

    double pi = h * sum;

    std::cout << std::setprecision(16) << "The approx. value of Pi is " << pi << std::endl;
    std::cout << std::setprecision(16) << "The closest value of Pi is " << M_PI << std::endl;
}