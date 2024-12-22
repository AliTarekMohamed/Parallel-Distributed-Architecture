#include <mpi.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int interval = 0;
	double *pi_sums = new double[size], local_pi = 0.0, sum = 0.0;

	if (rank == 0)
	{
		interval = 1000000;
	}

	MPI_Bcast(&interval, 1, MPI_INT, 0, MPI_COMM_WORLD);

	double h = 1.0 / double(interval * size);
	int start = rank * interval;
	int end = (rank + 1) * interval;

	for (int i = start; i < end; i++)
	{
		double x = h * ((double)i - 0.5);
		sum += (4 / (1 + pow(x, 2)));
	}

	local_pi = h * sum;

	MPI_Gather(&local_pi, 1, MPI_DOUBLE, pi_sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		double pi = 0.0;
		for (int i = 0; i < size; i++)
		{
			pi += pi_sums[i];
		}
		printf("Pi = %f\n", pi);
	}

	MPI_Finalize();
	return 0;
}