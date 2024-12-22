#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 100

int main()
{
	int i, a[N], b[N], local_result = 0, final_result = 0;

#pragma omp parallel shared (a, b, final_result) private (i, local_result)
	{
#pragma omp for schedule (dynamic, 10)
		for (i = 0; i < N; i++)
		{
			a[i] = b[i] = i + 1;
		}
#pragma omp barrier
#pragma omp single
		cout << "The arrays are filled Successfully!\n" << endl;

#pragma omp for schedule (dynamic, 10)
		for (i = 0; i < N; i++)
		{
			local_result += (a[i] * b[i]);
		}

#pragma omp critical
		final_result += local_result;

#pragma omp barrier
#pragma omp single
		printf("Final result = %d\n", final_result);
	}

	return 0;
}