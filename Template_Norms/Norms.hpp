#ifndef NORMS_HPP
#define NORMS_HPP

#include <algorithm>
#include <numeric>
#include <cmath>

template <typename Container>
class Norms
{
    const Container & myContainer;

public:
    Norms(Container const & c) : myContainer{c} {};

    template <unsigned int p, typename FAKE = void> struct Aux {
        static auto compute(const Container & myC) {
            Container aux(myC.size());
            std::transform(myC.cbegin(), myC.cend(),
                        aux.begin(), [](auto i){return std::pow(i, p);});

            return std::pow(std::accumulate(aux.cbegin(), aux.cend(), 0.),
                        1./static_cast<double>(p));
        }
    };

    template <typename FAKE> struct Aux<0, FAKE> {
        static auto compute(const Container & myC) {
            return std::count_if(myC.cbegin(), myC.cend(),
                                        [](auto i){return i;});
        }
    };

    template <unsigned int p>
    auto compute() const
    {       
        return Aux<p>::compute(myContainer);
    }
};

#endif