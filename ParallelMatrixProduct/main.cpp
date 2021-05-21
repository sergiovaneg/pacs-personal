#include <mpi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>

void readMatrix(std::vector<double> & matrix, unsigned& rows, unsigned& cols, const std::string & filename)
{
    std::ifstream data(filename, std::ifstream::in);
    std::string aux;

    std::getline(data,aux);
    if(aux.empty())
            return;
    std::istringstream line(aux);
    std::string field;

    std::getline(line, field, ',');
    rows = std::stoul(field);
    std::getline(line, field, ',');
    cols = std::stoul(field);

    matrix.reserve(rows*cols);

    while(std::getline(data, aux)){
        if(aux.empty())
            continue;

        std::istringstream line(aux);
        while(std::getline(line, field, ','))
            matrix.push_back(std::stod(field));
    }
}

void matrixProduct(const std::vector<double> & A, const std::vector<double> & x, std::vector<double> & b){
    for(size_t i = 0; i < b.size(); ++i)
        b[i] = std::inner_product(A.cbegin() + i * x.size(), A.cbegin() + (i+1) * x.size(), x.begin(), 0.);
}

void writeMatrix(const std::vector<double>& matrix, const unsigned & rows, const unsigned & cols, const std::string & filename){
    std::ofstream ofs(filename, std::ofstream::out | std::ofstream::trunc);
    ofs << rows << "," << cols;
    for(size_t i = 0; i < rows*cols; ++i){
        if(!(i%cols))
            ofs << std::endl;
        ofs << matrix[i] << ",";
    }
    ofs.flush();
}

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned rows, cols;
    std::vector<double> global_A;
    std::vector<double> x;
    std::vector<double> global_b;

    std::vector<int> send_count(size), send_offsets(size);

    if(!rank){
        readMatrix(global_A, rows, cols, "A.csv");
        unsigned dump;
        readMatrix(x, dump, dump, "x.csv");

        for(size_t i = 0; i < size; ++i){
            if(i < (rows % size)){
                send_count[i] = (std::floor(rows / size) + 1) * cols;
                send_offsets[i] = send_count[i] * i;
            }
            else{
                send_count[i] = std::floor(rows / size) * cols;
                send_offsets[i] = cols * (rows % size) + send_count[i] * i;
            }
        }
        global_b.resize(rows);
    }

    MPI_Bcast(&cols, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    x.resize(cols);

    int block_size, offset;

    MPI_Scatter(send_count.data(), 1, MPI_INT,
                &block_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(send_offsets.data(), 1, MPI_INT,
                &offset, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<double> A;
    A.resize(block_size);
    std::vector<double> b;
    b.resize(block_size/cols);

    MPI_Scatterv(global_A.data(), send_count.data(), send_offsets.data(), MPI_DOUBLE,
                    A.data(), block_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(x.data(), cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    matrixProduct(A, x, b);

    if(!rank)
        for(size_t i = 0; i < size; ++i){
            send_count[i] /= cols;
            send_offsets[i] /= cols;
        }

    MPI_Gatherv(b.data(), block_size/cols, MPI_DOUBLE,
                global_b.data(), send_count.data(), send_offsets.data(), MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    if(!rank){
        writeMatrix(global_b, rows, 1, "b.csv");
    }

    MPI_Finalize();
}