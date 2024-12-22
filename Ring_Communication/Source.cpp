#include <mpi.h>
#include <stdio.h>

int main()
{
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	int source = rank - 1;
	int destination = (rank + 1) % size;

	char message[] = "Hello World";
	int message_size = sizeof(message);
	char *recieved_message = new char[message_size]();

	if (rank == 0)
	{
		source = size - 1;
		MPI_Send(message, message_size, MPI_CHAR, destination, 0, MPI_COMM_WORLD);
		MPI_Recv(recieved_message, message_size, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);
		printf("%s from %d to %d", recieved_message, source, rank);
	}
	else
	{
		MPI_Recv(recieved_message, message_size, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);
		printf("%s from %d to %d", recieved_message, source, rank);
		MPI_Send(recieved_message, message_size, MPI_CHAR, destination, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}