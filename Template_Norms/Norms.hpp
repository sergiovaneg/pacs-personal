#ifndef NORMS_HPP
#define NORMS_HPP

#include <algorithm>
#include <numeric>
#include <cmath>

template <typename Container>
class Norms
{
    const Container & myContainer;

    template <unsigned int p, typename FAKE = void> struct Aux {
        static auto compute(const Container & myC) {
            return std::pow(std::accumulate(myC.cbegin(), myC.cend(), 0.,
                        [](auto const & x, auto const & y) {return x + std::pow(std::abs(y), p);}),
                        1./p);
        }
    };

    template <typename FAKE> struct Aux<0, FAKE> {
        static auto compute(const Container & myC) {
            return std::count_if(myC.cbegin(), myC.cend(),
                                        [](auto i){return i;});
        }
    };

    template <typename FAKE> struct Aux<1, FAKE> {
        static auto compute(const Container & myC) {
            return std::accumulate(myC.cbegin(), myC.cend(), 0.,
                        [](auto const & x, auto const & y) {return x + std::abs(y);});
        }
    };

public:
    Norms(Container const & c) : myContainer{c} {};

    template <unsigned int p>
    auto compute() const
    {       
        return Aux<p>::compute(myContainer);
    }
};

#endif