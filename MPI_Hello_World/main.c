#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
	int my_rank, numprocs;
	char message[100];
	int dest, tag, source;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	if (my_rank != 0)
	{
	sprintf(message,"Greetings from process %d !\0",my_rank);
	dest = 0;
	tag = 0;
	MPI_Send(message, sizeof(message),
		MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}
	else {
		for (source = 1; source <= (numprocs-1); source++)
		{
			MPI_Recv(message, 100, MPI_CHAR,
			source, tag, MPI_COMM_WORLD, &status);
		printf("%s\n",message);
		}
	}
	MPI_Finalize();
	return 0;
}
