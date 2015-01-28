
#include <stdlib.h>
#include <cuda.h>
#include <stdio.h>
# define WIN_SZ_X 1024
# define WIN_SZ_Y 1024

__global__ void		julia(int	*d_i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy, double c_i, double c_r)
{
	double	x1;
	double	y1;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;
	int		row;  // WIDTH
	int		col;  // HEIGHT
	int		index;
	row = blockIdx.y * blockDim.y + threadIdx.y;
	col = blockIdx.x * blockDim.x + threadIdx.x;
	index = row * winszx + col;
	if(col >= winszx || row >= winszy)
		return;

	x1 = -1.4;
	y1 = -1.2;
	z_r = (((double)col + (double)offx) / (double)zoom) + x1;
	z_i = (((double)row + (double)offy) / (double)zoom) + y1;
	i = 0;
	while((z_r * z_r + z_i * z_i) < 4 && i < ite_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + c_r;
		z_i = (2 * tmp * z_i) + c_i;
		i++;
	}
	d_i[index] = i;
}

extern "C" void		call_julia(int *i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy, double c_i, double c_r)
{
	int		*d_i;
	int		size;
	dim3	block_size(16, 16);
	dim3	grid_size(WIN_SZ_X / block_size.x, WIN_SZ_Y / block_size.y);

	size = WIN_SZ_Y * WIN_SZ_X * sizeof(int);
	cudaMalloc((void **)&d_i, size);
	julia<<<grid_size,block_size>>>(d_i, offx, offy, zoom, ite_max, winszx, winszy, c_i, c_r);

	cudaMemcpy(i, d_i, size, cudaMemcpyDeviceToHost);
	cudaFree(d_i);
}
