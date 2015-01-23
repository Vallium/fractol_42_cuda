
#include <stdlib.h>
#include <cuda.h>
//#include "cuda_call.h"
#include <stdio.h>
#define N 512

__global__ void		add(double *a, double *b, double *c)
{
	c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

extern "C" void		call_add(void)
{
	double *a, *b, *c;
	double *d_a, *d_b, *d_c;
	double size = N * sizeof(double);
	int		i;

	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	a = (double *)malloc(size);
	b = (double *)malloc(size);
	c = (double *)malloc(size);

	for (i = 0; i < N; ++i)
	{
		a[i] = rand() % 10;
		b[i] = rand() % 10;
	}

	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

	add<<<1,N>>>(d_a, d_b, d_c);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

	for (i = 0; i < N; ++i)
		printf("%f + %f = %f\n", a[i], b[i], c[i]);
	free(a);
	free(b);
	free(c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
//	return (0);
}
