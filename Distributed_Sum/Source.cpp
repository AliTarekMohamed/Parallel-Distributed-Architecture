#include <mpi.h>
#include <stdio.h>

#define N 15
#define num_of_threads 3

int main()
{
	MPI_Init(NULL, NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status status;

	const int chunk = N / num_of_threads;
	int arr[N];

	for (int i = 0; i < N; i++)
	{
		arr[i] = i + 1;
	}

	if (rank == 0)
	{
		MPI_Send(&arr[5], chunk, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&arr[10], chunk, MPI_INT, 2, 0, MPI_COMM_WORLD);

		int sums[num_of_threads], local_sum = 0, final_sum = 0;

		for (int i = 0; i < chunk; i++)
		{
			local_sum += arr[i];
		}

		sums[0] = local_sum;
		MPI_Recv(&sums[1], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&sums[2], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);

		for (int i = 0; i < num_of_threads; i++)
		{
			final_sum += sums[i];
		}

		printf("Final result = %d\n", final_sum);
	}
	else if (rank <= 2)
	{
		int sub_arr[chunk], local_sum = 0;
		MPI_Recv(&sub_arr, chunk, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		for (int i = 0; i < chunk; i++)
		{
			local_sum += sub_arr[i];
		}

		MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}


	MPI_Finalize();
	return 0;
}