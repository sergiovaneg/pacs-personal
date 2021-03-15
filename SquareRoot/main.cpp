#include <iostream>
#include <complex>
#include <algorithm>
#include <cmath>

double my_sqrt(double x, double tol, double y)
{
	double yy = 0.5 * (y + x/y);
	if(std::abs(yy-y)< tol)
		return yy;
	else
		return my_sqrt(x, tol, yy);
}

std::complex<double> my_sqrt(double x, double tol)
{
	if(!x)
		return 0.;

	if(x > 0)
		return my_sqrt(x, tol, 0.5*std::max(x, 1.));
	else
		return std::complex<double>(0., my_sqrt(std::abs(x), tol, std::max(std::abs(x), 1.) / 2));
}

int main(int argc, char** argv)
{
	if(argc == 3)
		std::cout << my_sqrt(std::stod(argv[1]), std::stod(argv[2])) << std::endl;
	else
		std::cout << my_sqrt(0, 0.0001) << std::endl;
}
