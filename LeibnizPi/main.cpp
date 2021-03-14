#include <iostream>

constexpr double LeibnizPi(unsigned n_it)
{
	double sum = 1.;
	double n = -3.;
	for(unsigned i = 0; i < n_it; i++){
		sum += 1 / n;
		n = (n > 0.) ? -(n + 2.) : -(n - 2.);
	}

	return sum * 4.;
}

int main(int argc, char** argv)
{
	constexpr unsigned default_n_it = 100;
 	unsigned n = (argc == 2) ? std::stoul(*(argv+1)) : default_n_it;

	std::cout << LeibnizPi(n) << std::endl;
}
