#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 100
#define CHUNK_SIZE 10

int main()
{
	int i, chunk, a[N], b[N], result = 0;

	for (i = 0; i < N; i++) {
		a[i] = b[i] = i + 1;
	}

	chunk = CHUNK_SIZE;

#pragma omp parallel for default (shared) private (i) schedule (dynamic, chunk) reduction (+:result)
	for (i = 0; i < N; i++)
	{
		result += (a[i] * b[i]);
	}

	printf("Final result = %d\n", result);

	return 0;
}