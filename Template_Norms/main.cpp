#include "Norms.hpp"

#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
    std::vector<double> v{1,-2,3,4};
    Norms<std::vector<double>> norm(v);

    std::cout << norm.compute<0>() << std::endl;
    std::cout << norm.compute<1>() << std::endl;
    std::cout << norm.compute<2>() << std::endl;
}