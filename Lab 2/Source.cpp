#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
using namespace std;

#define N 100
#define CHUNK_SIZE 10

int main()
{
	int i, thread_id, a[N], b[N], c[N], chunk;

	for (i = 0; i < N; i++)
	{
		a[i] = b[i] = i + 1;
	}

	chunk = CHUNK_SIZE;

#pragma omp parallel shared (a, b, c, chunk) private (i, thread_id)
	{
		thread_id = omp_get_thread_num();

#pragma omp for schedule (dynamic, chunk)
		for (i = 0; i < N; i++)
		{
			c[i] = a[i] + b[i];
		}

		if (thread_id == 0)
		{
			for (i = 0; i < N; i++)
			{
				cout << c[i] << endl;
			}
		}
	}

	return 0;
}