#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 100

int main()
{

	int num_of_threads, thread_id, i;
	int a[N], b[N], c[N];

	for (i = 0; i < N; i++)
	{
		a[i] = b[i] = i + 1;
	}

	omp_set_num_threads(5);

#pragma omp parallel private (i, thread_id)
	{
		num_of_threads = omp_get_num_threads();
		thread_id = omp_get_thread_num();

		for (i = (thread_id * (N / num_of_threads)); i < ((thread_id + 1) * (N / num_of_threads)); i++)
		{
			c[i] = a[i] + b[i];
		}
	}

	for (i = 0; i < N; i++)
	{
		cout << c[i] << endl;
	}

	return 0;
}