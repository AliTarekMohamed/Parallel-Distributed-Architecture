#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 1000
#define CHUNK_SIZE 50

int main()
{
	int i, thread_id, arr[N], target, chunk;

	cout << "Enter number to search: ";
	cin >> target;

	for (i = 0; i < N; i++)
	{
		arr[i] = (rand() % 100) + 1;
	}

	chunk = CHUNK_SIZE;

#pragma omp parallel shared (arr, target, chunk) private (i, thread_id)
	{
		thread_id = omp_get_thread_num();

#pragma omp for schedule (dynamic, chunk)
		for (i = 0; i < N; i++)
		{
			if (arr[i] == target)
			{
				printf("%d founded by thread %d at index %d\n", target, thread_id, i);
			}
		}
	}

	return 0;
}