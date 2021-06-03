#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "eigen3/Eigen/Eigen"

const Eigen::VectorXd transpose(const Eigen::VectorXd & a){
    return a.transpose();
}

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

    m.def("transpose", &transpose, "Eigen version of transpose");
}