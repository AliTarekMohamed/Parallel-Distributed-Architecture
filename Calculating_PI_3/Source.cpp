#include <mpi.h>
#include <omp.h>
#include <iostream>
using namespace std;

#define NBIN 10000

int main()
{
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int locb = NBIN / size;
	double x, pi, sum = 0.0, step = (1.0 / (double)NBIN);


#pragma omp parallel
	{
#pragma omp for private (x) reduction (+:sum) schedule (runtime)
		for (int i = (rank * locb); i < ((rank + 1) * locb); i++)
		{
			x = (i + 0.5) * step;
			sum += (4.0 / (1.0 + pow(x, 2)));
		}
	}

	sum *= step;
	MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("PI = %g\n", pi);
	}

	MPI_Finalize();
	return 0;
}