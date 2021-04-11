#ifndef NORMS_HPP
#define NORMS_HPP

#include <algorithm>
#include <numeric>
#include <cmath>
#include <type_traits>

template <typename Container>
class Norms
{
    const Container & myContainer;

    template <unsigned p>
    auto compute(std::integral_constant<unsigned, p>) const
    {
        return std::pow(std::accumulate(myContainer.cbegin(), myContainer.cend(), 0.,
                        [](auto const & x, auto const & y) {return x + std::pow(std::abs(y), p);}),
                        1./p);
    }

    auto compute(std::integral_constant<unsigned, 0>) const{
        return std::count_if(myContainer.cbegin(), myContainer.cend(), [](auto i){return i;});
    }

    auto compute(std::integral_constant<unsigned, 1>) const{
        return std::accumulate(myContainer.cbegin(), myContainer.cend(), 0.,
                                [](auto const & x, auto const & y) {return x + std::abs(y);});
    }

public:
    Norms(Container const & c) : myContainer{c} {};

    template <unsigned p>
    auto compute() const
    {       
        return compute(std::integral_constant<unsigned, p>());
    }
};

#endif