#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	int i, sum = 0, num_of_points = 100000000;
	double rand_x, rand_y, pi, tmp;

#pragma omp parallel default (shared) private (i, tmp, rand_x, rand_y) num_threads (16)
	{
#pragma omp for reduction (+:sum)
		for (i = 0; i < (int)num_of_points; i++)
		{
			rand_x = double(rand() % 100) / (double)100.0;
			rand_y = double(rand() % 100) / (double)100.0;
			tmp = pow(rand_x - 0.5, 2) + pow(rand_y - 0.5, 2);

			if (tmp <= 0.25)
			{
				sum++;
			}
		}
	}

	pi = 4.0 * ((double)sum / (double)num_of_points);
	printf("pi = %f\n", pi);

	return 0;
}