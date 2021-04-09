#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Copy constructor used to instantiate v
template <class T>
double fun1(T const & x){
    T v = x;

    return 0;
}

// Assumes x is movable, which is why it will cause an error if an lvalue is passed
template <class T>
double fun2(T&& x){
    T v = std::move(x);

    return 0;
}

// Deduces wether or not the object is movable
template <class T>
double fun3(T&& x){
    T v = std::forward<T>(x);

    return 0;
}

int main(int argc, char** argv){
    std::vector<double> v1{1000000, 10.};
    std::vector<double> v2{1000000, 10.};
    std::vector<double> v3{1000000, 10.};

    auto start1 = std::chrono::high_resolution_clock::now();
    fun1(v1);
    auto stop1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    fun2(v2);
    auto stop2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    fun3(std::move(v3));
    auto stop3 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count() << "\t"
                << v1.size() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2).count() << "\t"
                << v2.size() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop3 - start3).count() << "\t"
                << v3.size() << std::endl;
}