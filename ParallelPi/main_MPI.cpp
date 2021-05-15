#include <iostream>
#include <vector>
#include <mpi/mpi.h>

int main (int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<double> a(10);

    if(!rank) {
        std::fill(a.begin(), a.end(), 1.5);
        MPI_Send(a.data(), a.size(), MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    }
        
    else if(rank == 1){
        MPI_Status s;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &s);
        int count;
        MPI_Get_count(&s, MPI_DOUBLE, &count);
        MPI_Recv(a.data(), count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(auto& aux : a)
            std::cout << aux << " ";
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}