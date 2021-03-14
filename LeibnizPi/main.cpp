#include <iostream>
#include <vector>
#include <algorithm>

constexpr inline double int_pow(double base, double exponent)
{
	double result = 1.;
	for(unsigned i = 0; i < exponent; i++)
		result *= base;
	return result;
}

constexpr double LeibnizPi(unsigned n_it)
{
	double sum = 0.;
	unsigned n = 1;
	for(unsigned i = 0; i < n_it; i++){
		sum += 2. / (static_cast<double>(n * (n+2)));
		n += 4;
	}

	return sum * 4.;
}

double RichardExtPi(unsigned n_it, double t)
{
	std::vector<double> v1(n_it);
	std::vector<double> v2(n_it);

	unsigned h = 1;
	v1[0] = LeibnizPi(h);

	for(unsigned i = 1; i < n_it; i++){
		h*=t;
		v2[0] = LeibnizPi(h);

		for(unsigned j = 0; j < i; j++){
			const double c = int_pow(t, j+1);
			v2[j+1] = (c * v2[j] - v1[j]) / (c - 1);
		}

		std::swap(v1, v2);
	}

	return v1.back();
}

int main(int argc, char** argv)
{
	constexpr unsigned default_n_it = 10;
	constexpr double default_t = 2.;

 	unsigned n = (argc == 3) ? std::stoul(*(argv+1)) : default_n_it;
	unsigned t = (argc == 3) ? std::stod(*(argv+2)) : default_t;

	std::cout << RichardExtPi(n, t) << std::endl;
}
