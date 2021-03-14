#include <iostream>

using PF = double (*)(double);

inline double my_function(double x)
{
	return x*x;
}

double simpson(double a, double b, PF const f, unsigned n)
{
	double sum = 0.;
	double const h = (b - a) / static_cast<double>(n);

	double current_term = f(a);

	for(double i = 0.; i < static_cast<double>(n); i += 1.){
		double const next_term = f(a + (i + 1.) * h);
		sum += current_term + f(a + (i + 0.5) * h) + next_term;
		current_term = next_term;
	}

	return h * sum / 3.;
}

int main(int argc, char** argv)
{
	constexpr double default_a = 0.;
	constexpr double default_b = 1.;
	constexpr unsigned default_n = 10;

	double a, b;
	unsigned n;
	if(argc == 4){
		a = std::stod(*(argv + 1));
		b = std::stod(*(argv + 2));
		n = std::stoul(*(argv + 3));
	}
	else{
		a = default_a;
		b = default_b;
		n = default_n;
	}

	std::cout << simpson(a, b, my_function, n) << std::endl;
}
