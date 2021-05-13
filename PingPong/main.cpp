#include <mpi.h>
#include <string>
#include <iostream>

int main(int argc, char** argv){
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank%2){
        char a[4];
        MPI_Recv(a, 4, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << a << std::endl;
        char b[4]{'P','O','N','G'};
        MPI_Send(b, 4, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD);
    }
    else if((rank+1) < size){
        char a[4]{'P','I','N','G'};
        MPI_Send(a, 4, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
        char b[4];
        MPI_Recv(b, 4, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << b << std::endl;
    }

    MPI_Finalize();
    return 0;
}