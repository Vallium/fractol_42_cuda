
#include <stdlib.h>
#include <cuda.h>
#include <stdio.h>
#define N (2048 * 2048)
#define M 512

__global__ void		add(double *a, double *b, double *c, int n)
{
	int		index;

	index = threadIdx.x + blockIdx.x * blockDim.x;
	if (index < n)
		c[index] = a[index] + b[index];
}

extern "C" void		call_add(char * str)
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

	add<<<(N + M - 1) / M,M>>>(d_a, d_b, d_c, N);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

	for (i = 0; i < N; ++i)
		printf("%s -> %f + %f = %f\n", str, a[i], b[i], c[i]);
	free(a);
	free(b);
	free(c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
}
